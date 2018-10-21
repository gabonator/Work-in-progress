mkdir fs
sudo mount -t msdos /dev/disk2 fs
cp build/outmin.elf fs/noimport.elf
sudo umount fs
rmdir fs