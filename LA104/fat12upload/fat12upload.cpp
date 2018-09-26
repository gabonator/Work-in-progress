
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>                     
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctype.h>

#include <strings.h>
#include "bpb.h"
#include "bootsect.h"
#include "fat.h"
#include "direntry.h"

#define DEBUG
#define MAXPATHLEN 255

bool dooverwrite = true;
bool doformat = false;
bool docopy = true;
int __target = 2;

void _readdi(int fdi, direntry& dirent, int direntofs, bool);

void get_name(char *fullname, struct direntry *dirent) 
{
    char name[9];
    char extension[4];
    int i;

    name[8] = ' ';
    extension[3] = ' ';
    memcpy(name, &(dirent->deName[0]), 8);
    memcpy(extension, dirent->deExtension, 3);

    /* names are space padded - remove the padding */
    for (i = 8; i > 0; i--) {
	if (name[i] == ' ') 
	    name[i] = '\0';
	else 
	    break;
    }

    /* extensions aren't normally space padded - but remove the
       padding anyway if it's there */
    for (i = 3; i > 0; i--) {
	if (extension[i] == ' ') 
	    extension[i] = '\0';
	else 
	    break;
    }
    fullname[0]='\0';
    strcat(fullname, name);

    /* append the extension if it's not a directory */
    if ((dirent->deAttributes & ATTR_DIRECTORY) == 0) {
	strcat(fullname, ".");
	strcat(fullname, extension);
    }
}

uint16_t get_fat_entry(uint16_t clusternum, 
		       int fd, struct bpb33* bpb)
{
    uint32_t offset;
    uint16_t value;
    uint8_t b1, b2;
    
    /* this involves some really ugly bit shifting.  This probably
       only works on a little-endian machine. */
    offset = bpb->bpbResSectors * bpb->bpbBytesPerSec * bpb->bpbSecPerClust 
	+ (3 * (clusternum/2));

    printf("Get fat entry %d at %x...", clusternum, offset);	

    lseek(fd, offset, SEEK_SET);

    unsigned char sector[4] = {0};
    if (read(fd, sector, 4) != 4 || errno != 0)
      fprintf(stderr, "Read error!\n");

    switch(clusternum % 2) {
    case 0:
	b1 = sector[0]; //*(image_buf + offset);
	b2 = sector[1]; //*(image_buf + offset + 1);
	/* mjh: little-endian CPUs are ugly! */
	value = ((0x0f & b2) << 8) | b1;
	break;
    case 1:
	b1 = sector[1]; //*(image_buf + offset + 1);
	b2 = sector[2]; //*(image_buf + offset + 2);
	value = b2 << 4 | ((0xf0 & b1) >> 4);
	break;
    }
    printf(" => %x\n", value);
    return value;
}

void set_fat_entry(uint16_t clusternum, uint16_t value,
		   int fdi, struct bpb33* bpb)
{
    uint32_t offset;
    uint8_t *p1, *p2;
    
    /* this involves some really ugly bit shifting.  This probably
       only works on a little-endian machine. */
    offset = bpb->bpbResSectors * bpb->bpbBytesPerSec * bpb->bpbSecPerClust 
	+ (3 * (clusternum/2));

    printf("Set fat entry %d at %x value %x...", clusternum, offset, value);	

    lseek(fdi, offset, SEEK_SET);

    unsigned char sector[3] = {0};
    if (read(fdi, sector, 3) != 3 || errno != 0)
      fprintf(stderr, "Read error!\n");
//    printf("(rd 0x%x %02x %02x %02x)", offset, sector[0], sector[1], sector[2]);

    switch(clusternum % 2) {
    case 0:
	p1 = &sector[0]; //image_buf + offset;
	p2 = &sector[1]; //image_buf + offset + 1;
	/* mjh: little-endian CPUs are really ugly! */


	//  00 01 02 
        //  Aa Ba bb
	*p1 = (uint8_t)(0xff & value);
	*p2 = (uint8_t)((0xf0 & (*p2)) | (0x0f & (value >> 8)));
	break;
    case 1:
	p1 = &sector[1]; //image_buf + offset + 1;
	p2 = &sector[2]; //image_buf + offset + 2;

	*p1 = (uint8_t)((0x0f & (*p1)) | ((0x0f & value) << 4));
	*p2 = (uint8_t)(0xff & (value >> 4));
	break;
    }

//    printf("(wr 0x%x %02x %02x %02x)", offset, sector[0], sector[1], sector[2]);
    lseek(fdi, offset, SEEK_SET);

    if (write(fdi, sector, 3) != 3 || errno != 0)
      fprintf(stderr, "Write error!\n");

}


struct bpb33* check_bootsector(int fd)
{
    struct bootsector33* bootsect;
    struct byte_bpb33* bpb;  /* BIOS parameter block */
    struct bpb33* bpb2;

    unsigned char sector0[512] = {0};
    if (read(fd, sector0, 512) != 512 || errno != 0)
    {
      fprintf(stderr, "Read error!\n");
        return NULL;
    }

    bootsect = (struct bootsector33*)sector0;

    if (bootsect->bsJump[0] == 0xe9 ||
	(bootsect->bsJump[0] == 0xeb && bootsect->bsJump[2] == 0x90)) {
#ifdef DEBUG
	printf("Good jump inst\n");
#endif
    } else {
	fprintf(stderr, "illegal boot sector jump inst: %x%x%x\n", 
		bootsect->bsJump[0], bootsect->bsJump[1], 
		bootsect->bsJump[2]); 
        return NULL;
    } 

#ifdef DEBUG
    printf("OemName: %s\n", bootsect->bsOemName);
#endif

    if (bootsect->bsBootSectSig0 == BOOTSIG0
	&& bootsect->bsBootSectSig0 == BOOTSIG0) {
	//Good boot sector sig;
#ifdef DEBUG
	printf("Good boot sector signature\n");
#endif
    } else {
	fprintf(stderr, "Boot boot sector signature %x%x\n", 
		bootsect->bsBootSectSig0, 
		bootsect->bsBootSectSig1);
        return NULL;
    }

    bpb = (struct byte_bpb33*)&(bootsect->bsBPB[0]);

    /* bpb is a byte-based struct, because this data is unaligned.
       This makes it hard to access the multi-byte fields, so we copy
       it to a slightly larger struct that is word-aligned */
    bpb2 = (bpb33*)malloc(sizeof(struct bpb33));

    bpb2->bpbBytesPerSec = getushort(bpb->bpbBytesPerSec);
    bpb2->bpbSecPerClust = bpb->bpbSecPerClust;
    bpb2->bpbResSectors = getushort(bpb->bpbResSectors);
    bpb2->bpbFATs = bpb->bpbFATs;
    bpb2->bpbRootDirEnts = getushort(bpb->bpbRootDirEnts);
    bpb2->bpbSectors = getushort(bpb->bpbSectors);
    bpb2->bpbFATsecs = getushort(bpb->bpbFATsecs);
    bpb2->bpbHiddenSecs = getushort(bpb->bpbHiddenSecs);
    

#ifdef DEBUG
    printf("Bytes per sector: %d\n", bpb2->bpbBytesPerSec);
    printf("Sectors per cluster: %d\n", bpb2->bpbSecPerClust);
    printf("Reserved sectors: %d\n", bpb2->bpbResSectors);
    printf("Number of FATs: %d\n", bpb->bpbFATs);
    printf("Number of root dir entries: %d\n", bpb2->bpbRootDirEnts);
    printf("Total number of sectors: %d\n", bpb2->bpbSectors);
    printf("Number of sectors per FAT: %d\n", bpb2->bpbFATsecs);
    printf("Number of hidden sectors: %d\n", bpb2->bpbHiddenSecs);
#endif

    return bpb2;
}

int root_dir_addr(int fd, struct bpb33* bpb)
{
    uint32_t offset;
    offset = 
	(bpb->bpbBytesPerSec 
	 * (bpb->bpbResSectors + (bpb->bpbFATs * bpb->bpbFATsecs)));

//    printf("Root dir at %x\n", offset);
    return offset;
}


int cluster_to_addr_i(uint16_t cluster, int fd, 
			 struct bpb33* bpb)
{

    int offset = root_dir_addr(fd, bpb);

    if (cluster != MSDOSFSROOT) {
	/* move to the end of the root directory */
	offset += bpb->bpbRootDirEnts * sizeof(struct direntry);
	/* move forward the right number of clusters */
	offset += bpb->bpbBytesPerSec * bpb->bpbSecPerClust 
	    * (cluster - CLUST_FIRST);
    }
  return offset;
}

uint8_t *cluster_to_addr(uint16_t cluster, int fd, 
			 struct bpb33* bpb)
{
    printf("Cluster %d", cluster);

    int offset = cluster_to_addr_i(cluster, fd,bpb);

    printf(", reading at %x...", offset);

    static unsigned char sector[512] = {0};
    lseek(fd, offset, SEEK_SET);
    if (read(fd, sector, 512) != 512 || errno != 0)
      fprintf(stderr, "Read error!\n");
    printf(" ok\n");
    return sector;
}



#define FIND_FILE 0
#define FIND_DIR 1


void listfiles(uint16_t cluster, int fd, struct bpb33* bpb)
{
    char buf[MAXPATHLEN];
    char *seek_name, *next_name;
    int d;
    struct direntry dirent;
    uint16_t dir_cluster;
    printf("Listing files at cluster %d\n", cluster);
    int offset = cluster_to_addr_i(cluster, fd, bpb);
 
    /* find the first dirent in this directory */

    while (1) {

	for (d = 0; d < bpb->bpbBytesPerSec * bpb->bpbSecPerClust; 
	     d += sizeof(struct direntry) /*, offset += sizeof(struct direntry)*/) 
        {

      _readdi(fd, dirent, offset, false);

	    if (dirent.deName[0] == SLOT_EMPTY) {
		/* we failed to find the file */
		return;
	    }

//printf("pos:%d, direntname:%d\n", d, dirent.deName[0]);
printf("%c%c%c%c%c%c%c%c.%c%c%c attr:%02x low:%x, crea:%02x%02x%02x %02x%02x, high:%02x%02x, modif:%02x%02x %02x%02x, start:%02x%02x size:%02x%02x%02x%02x\n",
  dirent.deName[0],  dirent.deName[1],  dirent.deName[2],  dirent.deName[3],
  dirent.deName[4],  dirent.deName[5],  dirent.deName[6],  dirent.deName[7],
  dirent.deExtension[0],  dirent.deExtension[1],  dirent.deExtension[2],
  dirent.deAttributes,
  dirent.deLowerCase, 
  dirent.deCHundredth, dirent.deCTime[0], dirent.deCTime[1], dirent.deCDate[0], dirent.deCDate[1],
  dirent.deHighClust[0], dirent.deHighClust[1],
  dirent.deMTime[0], dirent.deMTime[1],  dirent.deMDate[0], dirent.deMDate[1],
  dirent.deStartCluster[1], dirent.deStartCluster[0],
  dirent.deFileSize[3], dirent.deFileSize[2], dirent.deFileSize[1], dirent.deFileSize[0]);

	    if (dirent.deName[0] == SLOT_DELETED) {
		/* skip over a deleted file */
         	offset += sizeof(direntry);
		continue;
	    }

	    offset += sizeof(direntry);
	}
	/* we've reached the end of the cluster for this directory.
	   Where's the next cluster? */
	if (cluster == 0) {
	    // root dir is special
	    offset += sizeof(direntry);
	} else {
	    cluster = get_fat_entry(cluster, fd, bpb);
            offset = cluster_to_addr_i(cluster, fd, bpb);
	}
    }

}

/*struct direntry* */ int find_file(char *infilename, uint16_t cluster,
			   int find_mode,
			   int fd, struct bpb33* bpb)
{
    char buf[MAXPATHLEN];
    char *seek_name, *next_name;
    int d;
    struct direntry dirent;
    uint16_t dir_cluster;
    char fullname[13];
    printf("Scanning file at cluster %d\n", cluster);
    int offset = cluster_to_addr_i(cluster, fd, bpb);
 
//    dirent = (struct direntry*)cluster_to_addr(cluster, fd, bpb);

    /* first we need to split the file name we're looking for into the
       first part of the path, and the remainder.  We hunt through the
       current directory for the first part.  If there's a remainder,
       and what we find is a directory, then we recurse, and search
       that directory for the remainder */

    strncpy(buf, infilename, MAXPATHLEN);
    seek_name = buf;

    /* trim leading slashes */
    while (*seek_name == '/' || *seek_name == '\\') {
	seek_name++;
    }

    /* search for any more slashes - if so, it's a dirname */
    next_name = seek_name;
    while (1) {
	if (*next_name == '/' || *next_name == '\\') {
	    *next_name = '\0';
	    next_name ++;
	    break;
	}
	if (*next_name == '\0') {
	    /* end of name - no slashes found */
	    next_name = NULL;
	    if (find_mode == FIND_DIR) {
		return offset;
	    }
	    break;
	}
	next_name++;
    }

    /* find the first dirent in this directory */

    while (1) {

	/* hunt a cluster for the relevant dirent.  If we reach the
	   end of the cluster, we'll need to go to the next cluster
	   for this directory */
//printf("bpbBytesPerSec:%d, bpbSecPerClust:%d\n", bpb->bpbBytesPerSec, bpb->bpbSecPerClust);
	for (d = 0; d < bpb->bpbBytesPerSec * bpb->bpbSecPerClust; 
	     d += sizeof(struct direntry) /*, offset += sizeof(struct direntry)*/) 
        {

      _readdi(fd, dirent, offset, true );
/*
//printf("pos:%d, direntname:%d\n", d, dirent.deName[0]);
printf("%c%c%c%c%c%c%c%c.%c%c%c attr:%02x low:%x, crea:%02x%02x%02x %02x%02x, high:%02x%02x, modif:%02x%02x %02x%02x, start:%02x%02x size:%02x%02x%02x%02x\n",
  dirent.deName[0],  dirent.deName[1],  dirent.deName[2],  dirent.deName[3],
  dirent.deName[4],  dirent.deName[5],  dirent.deName[6],  dirent.deName[7],
  dirent.deExtension[0],  dirent.deExtension[1],  dirent.deExtension[2],
  dirent.deAttributes,
  dirent.deLowerCase, 
  dirent.deCHundredth, dirent.deCTime[0], dirent.deCTime[1], dirent.deCDate[0], dirent.deCDate[1],
  dirent.deHighClust[0], dirent.deHighClust[1],
  dirent.deMTime[0], dirent.deMTime[1],  dirent.deMDate[0], dirent.deMDate[1],
  dirent.deStartCluster[0], dirent.deStartCluster[1],
  dirent.deFileSize[3], dirent.deFileSize[2], dirent.deFileSize[1], dirent.deFileSize[0]);
*/
	    if (dirent.deName[0] == SLOT_EMPTY) {
		/* we failed to find the file */
		return NULL;
	    }
	    if (dirent.deName[0] == SLOT_DELETED) {
		/* skip over a deleted file */
         	offset += sizeof(direntry);
		continue;
	    }
	    get_name(fullname, &dirent);
//	 printf("comp %s=%s\n", fullname, seek_name);

	    if (strcasecmp(fullname, seek_name)==0) {
		/* found it! */
		if ((dirent.deAttributes & ATTR_DIRECTORY) != 0) {
		    /* it's a directory */
		    if (next_name == NULL) {
			fprintf(stderr, "Cannot copy out a directory\n");
			exit(1);
		    }
		    dir_cluster = getushort(dirent.deStartCluster);
		    return find_file(next_name, dir_cluster, 
				     find_mode, fd, bpb);
		} else if ((dirent.deAttributes & ATTR_VOLUME) != 0) {
		    /* it's a volume */
		    fprintf(stderr, "Cannot copy out a volume\n");
		    exit(1);
		} else {
		    /* assume it's a file */
		    return offset;//dirent;
		}
	    }
	    offset += sizeof(direntry);
	}
	/* we've reached the end of the cluster for this directory.
	   Where's the next cluster? */
	if (cluster == 0) {
	    // root dir is special
	    offset += sizeof(direntry);
	} else {
	    cluster = get_fat_entry(cluster, fd, bpb);
            printf("Scanning file at NEXT cluster %d\n", cluster);

            offset = cluster_to_addr_i(cluster, fd, bpb);
//	    dirent = (struct direntry*)cluster_to_addr(cluster, 
//						       fd, bpb);
	}
    }
}

int topclust = 0;
uint16_t copy_in_file(FILE* fd, int fdi, struct bpb33* bpb, 
		      uint32_t *size)
{
    uint32_t clust_size, total_clusters, i;
    uint8_t *buf;
    size_t bytes;
    uint16_t start_cluster = 0;
    uint16_t prev_cluster = 0;
//    int lastWritten = 0x13;
    int lastWritten = __target;

    clust_size = bpb->bpbSecPerClust * bpb->bpbBytesPerSec;
    total_clusters = bpb->bpbSectors / bpb->bpbSecPerClust;
    buf = (uint8_t*)malloc(clust_size);

//int _base = 15;
    while(1) {

    memset(buf, 0, clust_size);

	/* read a block of data, and store it */
	bytes = fread(buf, 1, clust_size, fd);
	if (bytes > 0) {
//printf("read %d bytes - ", (int)bytes);
	    *size += bytes;

	    /* find a free cluster */

	    for (i = 2; i < total_clusters; i++) {
	        if (dooverwrite)
                {
                  if (i > lastWritten)
                  {
                    lastWritten = i;
                    break;
                  }
                } else
		if (get_fat_entry(i, fdi, bpb) == CLUST_FREE) {
		    break;
		}
	    }

//i = _base++;
	    if (i == total_clusters) {
		/* oops - we ran out of disk space */
		fprintf(stderr, "No more space in filesystem\n");
		/* we should clean up here, rather than just exit */ 
		exit(1);
	    }
printf("Found free cluster %d\n", i);

	    /* remember the first cluster, as we need to store this in
	       the dirent */
	    if (start_cluster == 0) {
		start_cluster = i;
topclust = i;
	    } else {
		/* link the previous cluster to this one in the FAT */
		assert(prev_cluster != 0);
		set_fat_entry(prev_cluster, i, fdi, bpb);
	    }
	    /* make sure we've recorded this cluster as used */
//TODO
	    set_fat_entry(i, FAT12_MASK&CLUST_EOFS, fdi, bpb);
//	    set_fat_entry(i, FAT12_MASK&CLUST_EOFE, fdi, bpb);

	    /* copy the data into the cluster */
            assert(clust_size == 512);
//	    memcpy(cluster_to_addr_(i, fdi, bpb), buf, clust_size);

            int targetOfs = cluster_to_addr_i(i, fdi, bpb);

            printf("Writing %d bytes cluster %x at %x... ", clust_size, i, targetOfs);

            lseek(fdi, targetOfs+0*0x400, SEEK_SET); // WTF?????????
            if (write(fdi, buf, clust_size) != clust_size || errno != 0)
              fprintf(stderr, "Write error!\n");

//printf("(sleeping)");
//usleep(0);
/*
             for (int q=0; q<512; q+=32)
{
            if (write(fdi, buf+q, 32) != 32 || errno != 0)
              fprintf(stderr, "Write error!\n");
}
*/
//            fsync(fdi);

/*
            unsigned char verify[512];
            printf("Verifying at %x...", targetOfs);

            lseek(fdi, targetOfs, SEEK_SET);
            if (read(fdi, verify, 512) != 512 || errno != 0)
              fprintf(stderr, "Read error!\n");

            for (int j=0; j<20; j++)
              printf("%c", verify[j]);

            for (int j=0; j<512; j++)
              if (verify[j] != buf[j])
              {
                 printf("%03x: %02x %02x\n", j, buf[j], verify[j]);
              }
*/
            printf(" ok\n");

	}
	if (bytes < clust_size) {
	    /* We didn't real a full cluster, so we either got a read
	       error, or reached end of file.  We exit anyway */
	    break;
	}
	prev_cluster = i;
    }

    free(buf);
    return start_cluster;
}

/* write the values into a directory entry */
void write_dirent(struct direntry *dirent, char *filename, 
		   uint16_t start_cluster, uint32_t size)
{
    char *p, *p2;
    char *uppername;
    int len, i;

    /* clean out anything old that used to be here */
    memset(dirent, 0, sizeof(struct direntry));

    /* extract just the filename part */
    uppername = strdup(filename);
    p2 = uppername;
    for (i = 0; i < strlen(filename); i++) {
	if (p2[i] == '/' || p2[i] == '\\') {
	    uppername = p2+i+1;
	}
    }

    /* convert filename to upper case */
    for (i = 0; i < strlen(uppername); i++) {
	uppername[i] = toupper(uppername[i]);
    }

    /* set the file name and extension */
    memset(dirent->deName, ' ', 8);
    p = strchr(uppername, '.');
    memcpy(dirent->deExtension, "___", 3);
    if (p == NULL) {
	fprintf(stderr, "No filename extension given - defaulting to .___\n");
    } else {
	*p = '\0';
	p++;
	len = strlen(p);
	if (len > 3) len = 3;
	memcpy(dirent->deExtension, p, len);
    }
    if (strlen(uppername)>8) {
	uppername[8]='\0';
    }
    memcpy(dirent->deName, uppername, strlen(uppername));
    free(p2);

    /* set the attributes and file size */
    dirent->deAttributes = ATTR_ARCHIVE;
    putushort(dirent->deStartCluster, start_cluster);
    putulong(dirent->deFileSize, size);

/*
printf("%c%c%c%c%c%c%c%c.%c%c%c attr:%02x low:%x, crea:%02x%02x%02x %02x%02x, high:%02x%02x, modif:%02x%02x %02x%02x, start:%02x%02x size:%02x%02x%02x%02x\n",
  dirent.deName[0],  dirent.deName[1],  dirent.deName[2],  dirent.deName[3],
  dirent.deName[4],  dirent.deName[5],  dirent.deName[6],  dirent.deName[7],
  dirent.deExtension[0],  dirent.deExtension[1],  dirent.deExtension[2],
  dirent.deAttributes,
  dirent.deLowerCase, 
  dirent.deCHundredth, dirent.deCTime[0], dirent.deCTime[1], dirent.deCDate[0], dirent.deCDate[1],
  dirent.deHighClust[0], dirent.deHighClust[1],
  dirent.deMTime[0], dirent.deMTime[1],  dirent.deMDate[0], dirent.deMDate[1],
  dirent.deStartCluster[0], dirent.deStartCluster[1],
  dirent.deFileSize[3], dirent.deFileSize[2], dirent.deFileSize[1], dirent.deFileSize[0]);
*/

/*
  dirent->deLowerCase = 0x18;
  dirent->deCHundredth = 0x02;
*/
  dirent->deCTime[0] = 0xd9;
  dirent->deCTime[1] = 0xa0;
  dirent->deCDate[0] = 0x37;
  dirent->deCDate[1] = 0x4d;

  dirent->deMTime[0] = 0x04;
  dirent->deMTime[1] = 0xb3;
  dirent->deMDate[0] = 0x36;
  dirent->deMDate[1] = 0x4d;

// OUTPUT  .RDY attr:20 low:18, crea:5ad09d 374d, high:0000, modif:804e 374d, start:0f00 size:0000087b
// OUTPUT  .ERR attr:20 low:0, crea:000000 0000, high:0000, modif:0001 0000, start:1400 size:00000733
// OUTPUT  .ERR attr:20 low:12, crea:5ad09d 374d, high:0000, modif:804f 374d, start:0f00 size:00000733
// OUTPUT  .ERR attr:20 low:18, crea:5ad09d 374d, high:0000, modif:804f 374d, start:0f00 size:00000733

// OUT     .RDY attr:20 low:18, crea:bfa3a0 374d, high:0000, modif:04b3 364d, start:1e00 size:000009c8
// OUT2    .RDY attr:20 low:18, crea:02d9a0 374d, high:0000, modif:04b3 364d, start:2800 size:000009c8

// OUTPUT  .ERR attr:20 low:18, crea:02d9a0 374d, high:0000, modif:04b4 364d, start:0f00 size:0000087b
    /* a real filesystem would set the time and date here, but it's
       not necessary for this coursework */

/*
OUT1    .RDY attr:20 low:18, crea:9b34ae 374d, high:0000, modif:04b3 364d, start:0f00 size:000009c8
OUT2    .RDY attr:20 low:18, crea:6636ae 374d, high:0000, modif:04b3 364d, start:1400 size:000009c8
OUT3    .RDY attr:20 low:18, crea:1a38ae 374d, high:0000, modif:04b3 364d, start:1900 size:000009c8
OUT4    .RDY attr:20 low:18, crea:9e39ae 374d, high:0000, modif:04b3 364d, start:1e00 size:000009c8

*/
}

void _readdi(int fdi, direntry& dirent, int direntofs, bool verb)
{
       if (verb)
        printf("Read direntry at %x", direntofs);
        lseek(fdi, direntofs, SEEK_SET);
        if (read(fdi, &dirent, sizeof(direntry)) != sizeof(direntry) || errno != 0)
          fprintf(stderr, "Read error! errno=%d \n", errno);
       if (verb)
        printf(" ok\n");
}

void _writedi(int fdi, direntry& dirent, int direntofs)
{
        printf("Updating direntry at %x", direntofs);
        lseek(fdi, direntofs, SEEK_SET);
        if (write(fdi, &dirent, sizeof(direntry)) != sizeof(direntry) || errno != 0)
          fprintf(stderr, "Write error!\n");
        printf(" ok\n");
}

void create_dirent(int direntofs, char *filename, 
		   uint16_t start_cluster, uint32_t size,
		   int fdi, struct bpb33* bpb)
{
    direntry dirent;

    if (dooverwrite)
    {
       // skip volume label
       direntofs += sizeof(direntry);
       write_dirent(&dirent, filename, start_cluster, size);
       _writedi(fdi, dirent, direntofs);

       direntofs += sizeof(direntry);
       memset((uint8_t*)&dirent, 0, sizeof(struct direntry));
       dirent.deName[0] = SLOT_EMPTY;
       _writedi(fdi, dirent, direntofs);
       return;
    }

//TODO:
	direntofs += sizeof(direntry)*10;

    while(1) {
        _readdi(fdi, dirent, direntofs, true);

	if (dirent.deName[0] == SLOT_EMPTY) {
	    /* we found an empty slot at the end of the directory */
	    write_dirent(&dirent, filename, start_cluster, size);
	    _writedi(fdi, dirent, direntofs);

	    direntofs += sizeof(direntry);

	    /* make sure the next dirent is set to be empty, just in
	       case it wasn't before */
	    memset((uint8_t*)&dirent, 0, sizeof(struct direntry));
	    dirent.deName[0] = SLOT_EMPTY;

	    _writedi(fdi, dirent, direntofs);

	    return;
	}
	if (dirent.deName[0] == SLOT_DELETED) {
	    /* we found a deleted entry - we can just overwrite it */
	    write_dirent(&dirent, filename, start_cluster, size);
	    _writedi(fdi, dirent, direntofs);
	    return;
	}

	direntofs += sizeof(direntry);
    }
}

void copyin(char *infilename, char* outfilename,
	     int fdi, struct bpb33* bpb)
{
//    struct direntry *dirent = (direntry*)NULL;
int direntofs = 0;


    FILE *fd;
    uint16_t start_cluster;
    uint32_t size = 0;

    /* check that the file doesn't already exist */
    direntofs = find_file(outfilename, 0, FIND_FILE, fdi, bpb);
    if (direntofs != 0) {
	fprintf(stderr, "File %s already exists\n", outfilename);
//	exit(1);
    }

printf("=============== BEFORE\n");
listfiles(0, fdi, bpb);
printf("===============\n");

printf("out:%s\n", outfilename);
    /* find the dirent of the directory to put the file in */
    direntofs = find_file(outfilename, 0, FIND_DIR, fdi, bpb);
    if (direntofs == 0) {
	fprintf(stderr, "Directory does not exists in the disk image\n");
	exit(1);
    }

    /* open the real file for reading */
    fd = fopen(infilename, "r");
    if (fd == NULL) {
	fprintf(stderr, "Can't open file %s to copy data in\n",
		infilename);
	exit(1); 
   }

//format
if (doformat)
{
    // clear second file record
    direntry dirent;
    memset((uint8_t*)&dirent, 0, sizeof(struct direntry));
    dirent.deName[0] = SLOT_EMPTY;
    _writedi(fdi, dirent, 16416);

    int total_clusters = bpb->bpbSectors / bpb->bpbSecPerClust;
    for (int i = 2; i < total_clusters; i++) 
      set_fat_entry(i, CLUST_FREE, fdi, bpb);
}
/*
  {uint8_t tabbuf[16];
  lseek(fdi, 0x1015, SEEK_SET);
  read(fdi, tabbuf, 16);
  printf("pre-table: ");
  for (int i=0; i<16; i++)
    printf("%02x ", tabbuf[i]);
  printf("\n");}
*/
if (docopy)
{
    /* do the actual copy in*/
    start_cluster = copy_in_file(fd, fdi, bpb, &size);

    /* create the directory entry */
    create_dirent(direntofs, outfilename, start_cluster, size, fdi, bpb);
      set_fat_entry(0, 0xfff, fdi, bpb);
//    for (int i = 7; i < 20; i++) 
//      set_fat_entry(i, 0, fdi, bpb);

/*
printf("=============== AFTER\n");
listfiles(0, fdi, bpb);
printf("===============\n");
*/
}    

    for (int i = 0; i < 20; i++) 
      get_fat_entry(i,  fdi, bpb);

if (0)
{

  {uint8_t tabbuf[16];
  lseek(fdi, 0x1015, SEEK_SET);
  read(fdi, tabbuf, 16);
  printf("post-table: ");
  for (int i=0; i<16; i++)
    printf("%02x ", tabbuf[i]);
  printf("\n");}

    for (int i = 0; i < 20; i++) 
      get_fat_entry(i, fdi, bpb);

    int offset = cluster_to_addr_i(0xf, fdi, bpb);
printf("Check for cluster 0x0f at %0x\n", offset);
unsigned char buffer[128];
	        lseek(fdi, offset, SEEK_SET);
        if (read(fdi, buffer, sizeof(buffer)) != sizeof(buffer) || errno != 0)
          fprintf(stderr, "read error\n");

  for (int i =0; i<50; i++)
    printf("%c", buffer[i]);
  printf("\n");
}

    fclose(fd);
}

int is_end_of_file(uint16_t cluster) {
    if (cluster >= (FAT12_MASK & CLUST_EOFS)
	&& cluster <= (FAT12_MASK & CLUST_EOFE)) {
	return true;
    } else 
	return false;
}
bool ilnum(char c)
{
  return isalnum(c) || c == ' ' || c == 0x0d || c== 0x0a || c == ':';
}
void copy_out_file(uint16_t cluster, uint32_t bytes_remaining,
		   int fdi, struct bpb33* bpb)
{
    int total_clusters, clust_size;

    clust_size = bpb->bpbSecPerClust * bpb->bpbBytesPerSec;
    total_clusters = bpb->bpbSectors / bpb->bpbSecPerClust;
    if (cluster == 0) {
	fprintf(stderr, "Bad file termination\n");
	return;
    } else if (is_end_of_file(cluster)) {
	return;	
    } else if (cluster > total_clusters) {
	abort(); /* this shouldn't be able to happen */
    }

    /* map the cluster number to the data location */
    int offset = cluster_to_addr_i(cluster, fdi, bpb);
    printf("\nCluster %x at %x ===============\n", cluster, offset);
    if (bytes_remaining <= clust_size) {
	/* this is the last cluster */

	unsigned char buffer[512] = {0};
	lseek(fdi, offset, SEEK_SET);
        if (read(fdi, buffer, bytes_remaining) != bytes_remaining || errno != 0)
          fprintf(stderr, "read error\n");
        for (int i=0; i<bytes_remaining; i++)
          printf("%c", ilnum(buffer[i]) ? buffer[i] : '?');
    printf("\n Dump finished===============\n\n\n");
    } else {                                   
	/* more clusters after this one */

	unsigned char buffer[512];
	lseek(fdi, offset, SEEK_SET);
        if (read(fdi, buffer, 512) != 512 || errno != 0)
          fprintf(stderr, "read error\n");
        for (int i=0; i<512; i++)
          printf("%c", ilnum(buffer[i]) ? buffer[i] : '?');

	/* recurse, continuing to copy */
	copy_out_file(get_fat_entry(cluster, fdi, bpb), 
		      bytes_remaining - clust_size, fdi, bpb);
    }
    return;
}



int main(int argc, const char * argv[]) 
{
    int fd = open("/dev/disk2", O_RDWR);
//fcntl(fd, F_NOCACHE, 1);
    printf("descriptor: %d err:%d\n", fd, errno);
    if (fd<0)
    {
      fprintf(stderr, "Failed to open disk\n");
      return 1;
    }

if (argc==2)
{
docopy = false;
}
if (argc==3)
{
 __target =atoi(argv[2]);
printf("target = %x\n", __target);
}

    bpb33* bpb = 0;

    bpb = check_bootsector(fd);
    if (bpb)
//      copyin((char*)"output.hex", (char*)"output02.hex", fd, bpb);
//      copyin((char*)"output.hex", (char*)"zerox.err", fd, bpb);
      copyin((char*)"output.hex", (char*)"nieco.hex", fd, bpb);
//    fsync(fd);

//    close(fd);
if (1 && docopy)
{
//    fd = open("/dev/disk2", O_RDWR);
    printf("Dumping....\n");
    copy_out_file(topclust, 0x733, fd, bpb);

}
    close(fd);

    fd = open("/dev/disk2", O_RDWR);

if (1 && docopy)
{
    printf("Dumping. after close...\n");
    copy_out_file(topclust, 0x733, fd, bpb);
}
//    printf("Dumping....\n");
//    copy_out_file(0x0f, 0x87b, fd, bpb);

            unsigned char verify[512];

int vo = cluster_to_addr_i(topclust, fd, bpb);
printf("at %x:\n", vo);
            lseek(fd, vo, SEEK_SET);
            if (read(fd, verify, 512) != 512 || errno != 0)
              fprintf(stderr, "Read error!\n");
  for (int k=0; k<512; k++)
    printf("%c", ilnum(verify[k]) ? verify[k] : '?');
  printf("\n");

close(fd);

/*
int targetOfs = 0x9a00;
for (int i=0; i<10; i++)
{
printf("--------pass %d--------\n",i);

    int fd = open("/dev/disk2", O_RDWR);

            unsigned char verify[256];

for(int j=0x9a00; j<0x9a00+16*0x100; j+=0x100)
{
            printf("p %d, at %x...", i, j);

            lseek(fd, j, SEEK_SET);
            if (read(fd, verify, 256) != 256 || errno != 0)
              fprintf(stderr, "Read error!\n");
  for (int k=0; k<20; k++)
    printf("%c", verify[k]);
  printf("\n");
}


 char buffer[32];// = "Blbosticka prepisujem!";
sprintf(buffer, "Blbosticka %d...", i);
  int rewro = 0x9a00+i*256+ 0x0400;
  printf("Rewriting at %x message: %s\n", rewro, buffer);
	        lseek(fd, rewro, SEEK_SET);
        if (write(fd, buffer, sizeof(buffer)) != sizeof(buffer) || errno != 0)
          fprintf(stderr, "write error\n");
printf("\n");
//  usleep(1000);
    close(fd);
//usleep(1000*50);
}
*/
    return 0;
}


/*

Listing files at cluster 0
Root dir at 4000
DFU V3_6.1_D attr:08 low:0, crea:000000 0000, high:0000, modif:188d dd40, start:0000 size:00000000
B Inf.o      attr:0f low:0, crea:727200 6d00, high:7400, modif:6900 6f00, start:0000 size:0000006e
Syst.e       attr:0f low:0, crea:726d00 2000, high:6f00, modif:6c00 7500, start:0000 size:0065006d
SYSTEM~1.    attr:16 low:0, crea:5e6370 5d45, high:0000, modif:6470 5d45, start:0200 size:00000000
A._.T.r      attr:0f low:0, crea:7f6100 7300, high:6500, modif:7300 0000, start:0000 size:ffffffff
~1      .TRA attr:22 low:0, crea:4a8a5a 7945, high:0000, modif:8a5a 7945, start:0500 size:00001000
?RASHE~1.EFM attr:12 low:0, crea:478a5a 7945, high:0000, modif:8a5a 7945, start:0400 size:00000000
A.Tra.s      attr:0f low:0, crea:256800 6500, high:0000, modif:ffff ffff, start:0000 size:ffffffff
TRASHE~1.    attr:12 low:0, crea:478a5a 7945, high:0000, modif:8a5a 7945, start:0400 size:00000000
A.fse.v      attr:0f low:0, crea:da6500 6e00, high:7300, modif:6400 0000, start:0000 size:ffffffff
FSEVEN~1.    attr:12 low:0, crea:4d8a5a 7945, high:0000, modif:8a5a 7945, start:0d00 size:00000000
TEST    .RDY attr:20 low:0, crea:c3c4b1 374d, high:0000, modif:97b2 374d, start:0f00 size:0000006b



*/