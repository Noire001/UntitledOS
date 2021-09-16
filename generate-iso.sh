mkdir -p "$1"/build/x86_64/isofiles/boot/grub
cp "$1"/build/x86_64/kernel/UntitledOS.bin "$1"/build/x86_64/isofiles/boot/UntitledOS.bin
echo 'set timeout=0
      set default=0
      menuentry "Untitled OS" {
          multiboot2 /boot/UntitledOS.bin
          boot
      }' > "$1"/build/x86_64/isofiles/boot/grub/grub.cfg
grub-mkrescue -o "$1"/build/x86_64/UntitledOS.iso "$1"/build/x86_64/isofiles
wait
echo 'cleaning up...'
rm -rf "$1"/build/x86_64/isofiles