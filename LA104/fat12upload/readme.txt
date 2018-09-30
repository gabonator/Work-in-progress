The FAT12 filesystem implementation in LA104 and DS203 both if unreliable. Automatic mounting
on Mac OSX causes to write some folders and files what leads to filesystem corruption. 
It is not possible to copy files reliably when the unit is mounted using mount unix command, 
nor using diskutil command. This utility allows to write directly to the unit even when
not mounted. It opens block device /dev/disk2, reads the FAT12 table and uploads wanted file.
It also allows to perform simple device format.

To use this tool:
    * disable automatic mounting as described here https://discussions.apple.com/docs/DOC-7942 
    * run 'sudo vifs'
    * add similar line as this 'UUID=0C6BB56F-CEA7-3564-A81A-FB98D5C3BC33 none msdos rw,noauto'
    * run 'sudo automount -vc'
    * run 'sudo ./fat12upload /dev/disk2 cp myfile.hex myfile.hex 18' to upload the file starting at cluster 18

Calling this utility forces creation of new file at specified cluster. After writing all data clusters,
directory entry is added to root folder.

Other methods:
    * run 'sudo ./fat12upload /dev/disk2 info' to verify if the device path is correct
    * run 'sudo ./fat12upload /dev/disk2 cp myfile.hex myfile.hex'
    * run 'sudo ./fat12upload /dev/disk2 cp myfile.hex myfile.hex 18' to upload the file starting at cluster 18
    * run 'sudo ./fat12upload /dev/disk2 fat' to show fat table
    * run 'sudo ./fat12upload /dev/disk2 clfat' to clear fat table
    * run 'sudo ./fat12upload /dev/disk2 ls' to list root folder
    * run 'sudo ./fat12upload /dev/disk2 ls 2' to list folder at cluster 2
    * run 'sudo ./fat12upload /dev/disk2 cldir' to clear root folder
    * run 'sudo ./fat12upload /dev/disk2 read 16' to show contents of sector 16 (0x10)

Problems: 
    * currently it can only upload files smaller than 3584 byes (7 sectors) for some unknown reason

Credits:
    * based on this project: https://github.com/qihaiyan/fat12.git