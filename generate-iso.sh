mkdir -p "$1"/build/x86_64/isofiles/boot/grub
cp "$1"/build/x86_64/kernel/UntitledOS.bin "$1"/build/x86_64/isofiles/boot/UntitledOS.bin
cp "$1"/boot/grub.cfg "$1"/build/x86_64/isofiles/boot/grub/grub.cfg
grub-mkrescue -o "$1"/build/x86_64/UntitledOS.iso "$1"/build/x86_64/isofiles
wait
echo 'cleaning up...'
rm -rf "$1"/build/x86_64/isofiles