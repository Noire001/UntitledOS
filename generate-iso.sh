mkdir -p ../build/x86_64/isofiles/boot/grub
cp ../build/x86_64/kernel/UntitledOS.bin ../build/x86_64/isofiles/boot/UntitledOS.bin
echo 'set timeout=0
      set default=0
      menuentry "Untitled OS" {
          multiboot2 /boot/UntitledOS.bin
          boot
      }' > ../build/x86_64/isofiles/boot/grub/grub.cfg
grub-mkrescue -o ../build/x86_64/UntitledOS.iso ../build/x86_64/isofiles
rm -rf ../build/x86_64/isofiles