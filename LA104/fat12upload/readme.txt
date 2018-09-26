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
    * run 'fat12upload /dev/disk2 info' to verify if the path is correct (TBD)
    * run 'fat12upload /dev/disk2 cp myfile.hex myfile.hex' (TBD)
    * if it does not work, try 'fat12upload /dev/disk2 format' and then copy again (TBD)
    * or try 'fat12upload /dev/disk2 ovr myfile.hex myfile.hex' (TBD)


To flash firmware, place your build into file called "output.hex" and call "sudo /.fat12upload a 17",
to list the filesystem call "sudo /.fat12upload a". The device is expected to be at path /dev/disk2.