IMAGE_NAME := moss

# literally just to compile limine limine
CC := cc
CFLAGS := -g -O2 -pipe
CPPFLAGS :=
LDFLAGS :=
LIBS :=

OVMF := extern/ovmf
LIMINE := extern/limine

BUILDDIR := kernel/build

.PHONY: run
run: all run-uefi

.PHONY: all
all: $(IMAGE_NAME).iso

.PHONY: all-hdd
all-hdd: $(IMAGE_NAME).hdd

# .PHONY: qemu
# qemu: $(IMAGE_NAME).iso
# 	qemu-system-x86_64 -M q35 -m 2G -cdrom $(IMAGE_NAME).iso -boot d

.PHONY: run-uefi
run-uefi: $(OVMF) $(IMAGE_NAME).iso
	qemu-system-x86_64 -M q35 -m 2G -bios $(OVMF)/OVMF.fd -cdrom $(IMAGE_NAME).iso -boot d -monitor stdio -vga std

.PHONY: run-hdd
run-hdd: $(IMAGE_NAME).hdd
	qemu-system-x86_64 -M q35 -m 2G -hda $(IMAGE_NAME).hdd

.PHONY: run-hdd-uefi
run-hdd-uefi: $(OVMF) $(IMAGE_NAME).hdd
	qemu-system-x86_64 -M q35 -m 2G -bios $(OVMF)/OVMF.fd -hda $(IMAGE_NAME).hdd

$(OVMF):
	mkdir -p $(OVMF)
	cd $(OVMF) && curl -Lo OVMF.fd https://retrage.github.io/edk2-nightly/bin/RELEASEX64_OVMF.fd

$(LIMINE):
	git clone https://github.com/limine-bootloader/limine.git --branch=v7.x-binary --depth=1 $(LIMINE)
	$(MAKE) -C $(LIMINE)

.PHONY: kernel
kernel:
	$(MAKE) -C kernel

$(IMAGE_NAME).iso: $(LIMINE) kernel
	rm -rf iso_root
	mkdir -p iso_root/boot
	cp -v $(BUILDDIR)/bin/moss iso_root/boot/
	mkdir -p iso_root/boot/limine
	cp -v limine.cfg $(LIMINE)/limine-bios.sys $(LIMINE)/limine-bios-cd.bin \
		$(LIMINE)/limine-uefi-cd.bin iso_root/boot/limine/

	mkdir -p iso_root/EFI/BOOT
	cp -v $(LIMINE)/BOOTX64.EFI iso_root/EFI/BOOT/
	cp -v $(LIMINE)/BOOTIA32.EFI iso_root/EFI/BOOT/

	xorriso -as mkisofs -b boot/limine/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot boot/limine/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o $(IMAGE_NAME).iso

	./$(LIMINE)/limine bios-install $(IMAGE_NAME).iso
	# rm -rf iso_root

$(IMAGE_NAME).hdd: $(LIMINE) kernel
	rm -f $(IMAGE_NAME).hdd
	dd if=/dev/zero bs=1M count=0 seek=64 of=$(IMAGE_NAME).hdd
	sgdisk $(IMAGE_NAME).hdd -n 1:2048 -t 1:ef00
	./$(LIMINE)/limine bios-install $(IMAGE_NAME).hdd
	mformat -i $(IMAGE_NAME).hdd@@1M

	mmd -i $(IMAGE_NAME).hdd@@1M ::/EFI ::/EFI/BOOT ::/boot ::/boot/limine

	mcopy -i $(IMAGE_NAME).hdd@@1M $(BUILDDIR)/bin/moss ::/boot
	mcopy -i $(IMAGE_NAME).hdd@@1M limine.cfg $(LIMINE)/limine-bios.sys ::/boot/limine
	mcopy -i $(IMAGE_NAME).hdd@@1M $(LIMINE)/BOOTX64.EFI ::/EFI/BOOT
	mcopy -i $(IMAGE_NAME).hdd@@1M $(LIMINE)/BOOTIA32.EFI ::/EFI/BOOT

.PHONY: clean
clean:
	rm -rf iso_root $(IMAGE_NAME).iso $(IMAGE_NAME).hdd
	$(MAKE) -C kernel clean

.PHONY: distclean
distclean: clean
	rm -rf $(LIMINE) $(OVMF)
