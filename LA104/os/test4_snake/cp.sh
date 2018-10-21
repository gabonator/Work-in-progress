mkdir fs
sudo mount -t msdos /dev/disk2 fs
cp build/snake.elf fs/snake.elf
sudo umount fs
rmdir fs