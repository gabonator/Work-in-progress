mkdir fs
sudo mount -t msdos /dev/disk2 fs
cp build/outmin.elf fs/import.elf
sudo umount fs
rmdir fs