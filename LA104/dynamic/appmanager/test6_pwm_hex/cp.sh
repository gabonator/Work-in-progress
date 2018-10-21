mkdir fs
sudo mount -t msdos /dev/disk2 fs
cp build/output.hex fs/pwm.hex
sudo umount fs
rmdir fs