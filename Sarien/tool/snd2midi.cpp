// snd2midi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef signed long int32;
typedef unsigned char byte;
FILE *_fd = NULL;
FILE *_f = NULL;
int _index = 0;
class Common {
public:
class MemoryWriteStreamDynamic
{
public:
		void write(char* buf, int l)
		{
			if (!_f)return;
			fwrite(buf, 1, l, _f);
		}
		void writeUint32BE(int l)
		{
			if (!_f)return;
			unsigned char *arr = (unsigned char*)&l;
			fwrite(&arr[3], 1, 1, _f);
			fwrite(&arr[2], 1, 1, _f);
			fwrite(&arr[1], 1, 1, _f);
			fwrite(&arr[0], 1, 1, _f);
		}
		void writeUint16BE(int l)
		{
			if (!_f)return;
			unsigned char *arr = (unsigned char*)&l;
			fwrite(&arr[1], 1, 1, _f);
			fwrite(&arr[0], 1, 1, _f);
		}
		void writeByte(int l)
		{
			if (!_f)return;
			byte b = l;
			fwrite(&b, 1, 1, _f);
		}
		int pos()
		{
			if (!_f)return 0;
			return ftell(_f);
		}
		void seek(int ofs, int mode)
		{
			if (!_f)return;
			fseek(_f, ofs, mode);
		}
};
};

#define SPEED_FACTOR 6

unsigned char instr[] = {0, 0, 0};

static void writeDelta(Common::MemoryWriteStreamDynamic *st, int32 delta) {
        int32 i;

        i = delta >> 21; if (i > 0) st->writeByte((i & 127) | 128);
        i = delta >> 14; if (i > 0) st->writeByte((i & 127) | 128);
        i = delta >> 7; if (i > 0) st->writeByte((i & 127) | 128);
        st->writeByte(delta & 127);
}
static uint32 convertSND2MIDI(byte *snddata, byte **data) {
        int32 lp, ep;
        int n;
        double ll;

        Common::MemoryWriteStreamDynamic st;

        ll = log10(pow(2.0, 1.0 / 12.0));

        /* Header */
        st.write("MThd", 4);
        st.writeUint32BE(6);
        st.writeUint16BE(1); /* mode */
        st.writeUint16BE(3); /* number of tracks */
        st.writeUint16BE(192); /* ticks / quarter */

		fprintf(_fd, "window.sound%d = [\n", _index);

		for (n = 0; n < 3; n++) {
                uint16 start, end, pos;

                st.write("MTrk", 4);
                lp = st.pos();
                st.writeUint32BE(0); /* chunklength */
                writeDelta(&st, 0); /* set instrument */
                st.writeByte(0xc0 + n);
                st.writeByte(instr[n]);
                start = snddata[n * 2 + 0] | (snddata[n * 2 + 1] << 8);
                end = ((snddata[n * 2 + 2] | (snddata[n * 2 + 3] << 8))) - 5;
				fprintf(_fd, "  [");
				bool first = true;
                for (pos = start; pos < end; pos += 5) {
                        uint16 freq, dur;
                        dur = (snddata[pos + 0] | (snddata[pos + 1] << 8)) * SPEED_FACTOR;
                        freq = ((snddata[pos + 2] & 0x3F) << 4) + (snddata[pos + 3] & 0x0F);
                        if (snddata[pos + 2] > 0) {
                                double fr;
                                int note;
                                /* I don't know, what frequency equals midi note 0 ... */
                                /* This moves the song 4 octaves down: */
                                fr = (log10(111860.0 / (double)freq) / ll) - 48;
                                note = (int)floor(fr + 0.5);
                                if (note < 0) note = 0;
                                if (note > 127) note = 127;
                                /* note on */
                                writeDelta(&st, 0);
                                st.writeByte(144 + n);
                                st.writeByte(note);
                                st.writeByte(100);
                                /* note off */
                                writeDelta(&st, dur);
                                st.writeByte(128 + n);
                                st.writeByte(note);
                                st.writeByte(0);
								if ( first )
									first = false;
								else
									fprintf(_fd, ",");
								fprintf(_fd, "%d,%d", note, dur/SPEED_FACTOR);
                        } else {
                                /* note on */
                                writeDelta(&st, 0);
                                st.writeByte(144 + n);
                                st.writeByte(0);
                                st.writeByte(0);
                                /* note off */
                                writeDelta(&st, dur);
                                st.writeByte(128 + n);
                                st.writeByte(0);
                                st.writeByte(0);

								if ( first )
									first = false;
								else
									fprintf(_fd, ",");
								fprintf(_fd, "%d,%d", -1, dur/SPEED_FACTOR);
                        }
                }
				fprintf(_fd, n<2 ? "],\n" : "]\n");

                writeDelta(&st, 0);
                st.writeByte(0xff);
                st.writeByte(0x2f);
                st.writeByte(0x0);
                ep = st.pos();
                st.seek(lp, SEEK_SET);
                st.writeUint32BE((ep - lp) - 4);
                st.seek(ep, SEEK_SET);
        }
				fprintf(_fd, "];\n");

//        *data = st.getData();

        return st.pos();
}

int _tmain(int argc, _TCHAR* argv[])
{
	for (int i=0; i<50; i++)
	{
		_index = i;
		char strifile[50], strofile[50];
		sprintf(strifile, "C:\\Temp\\sarien\\kq2_export\\Sound%d.ags", i);
		sprintf(strofile, "C:\\Temp\\sarien\\kq2_export\\sound%d.js", i);
		FILE *fin = fopen(strifile, "rb");
		if ( fin == NULL )
			continue;
		fseek(fin,0,SEEK_END);
		int size = ftell(fin);
		fseek(fin, 0, SEEK_SET);
		char *buf = new char[size];
		fread(buf, 1, size, fin);
		fclose(fin);

		FILE *fout = fopen(strofile, "w");
		_fd = fout;
		convertSND2MIDI((byte*)buf, NULL);
		fclose(fout);
		delete buf;
	}
	return 0;
}

