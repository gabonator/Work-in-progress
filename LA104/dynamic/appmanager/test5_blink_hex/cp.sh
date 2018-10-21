mkdir fs
sudo mount -t msdos /dev/disk2 fs
cp build/output.hex fs/blink.hex
sudo umount fs
rmdir fs