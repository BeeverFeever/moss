#!/usr/bin/env bash

set -xe

SCRIPTPATH=$(dirname "$0")
cd "$SCRIPTPATH"

SYSROOT=../sysroot
KERNELDIR=../kernel/build
LIMINE=../extern/limine
IMAGE_NAME=moss

mkdir -p "$SYSROOT"/boot
cp -uv "$KERNELDIR"/bin/moss "$SYSROOT"/boot/
mkdir -p "$SYSROOT"/boot/limine
cp -uv "$LIMINE"/limine-bios.sys "$LIMINE"/limine-bios-cd.bin \
   "$LIMINE"/limine-uefi-cd.bin "$SYSROOT"/boot/limine/

mkdir -p "$SYSROOT"/EFI/BOOT
cp -uv "$LIMINE"/BOOTX64.EFI "$SYSROOT"/EFI/BOOT/
cp -uv "$LIMINE"/BOOTIA32.EFI "$SYSROOT"/EFI/BOOT/

xorriso -as mkisofs -b boot/limine/limine-bios-cd.bin \
   -no-emul-boot -boot-load-size 4 -boot-info-table \
   --efi-boot boot/limine/limine-uefi-cd.bin \
   -efi-boot-part --efi-boot-image --protective-msdos-label \
   ../sysroot -o "$IMAGE_NAME".iso

./"$LIMINE"/limine bios-install "$IMAGE_NAME".iso
