IMAGE_NAME := moss

BUILDDIR := kernel/build
SYSROOT := sysroot

OVMF := extern/ovmf
LIMINE := extern/limine

.PHONY: run
run: all run-uefi

.PHONY: all
all: $(IMAGE_NAME).iso

.PHONY: run-uefi
run-uefi: $(OVMF) $(IMAGE_NAME).iso
	qemu-system-x86_64 -M q35 -m 2G -bios $(OVMF)/OVMF.fd -cdrom $(IMAGE_NAME).iso -enable-kvm -serial file:serial.log

# no support for hdd anymore, if it becomes useful in the future i can triffle through the old commits
# and find the build target for it
# .PHONY: run-hdd
# run-hdd: $(IMAGE_NAME).hdd
# 	qemu-system-x86_64 -M q35 -m 2G -hda $(IMAGE_NAME).hdd
# .PHONY: all-hdd
# all-hdd: $(IMAGE_NAME).hdd

$(OVMF):
	mkdir -p $(OVMF)
	cd $(OVMF) && curl -Lo OVMF.fd https://retrage.github.io/edk2-nightly/bin/RELEASEX64_OVMF.fd

$(LIMINE):
	git clone https://github.com/limine-bootloader/limine.git --branch=v7.x-binary --depth=1 $(LIMINE)
	$(MAKE) -C $(LIMINE)

.PHONY: kernel 
kernel:
	$(MAKE) -C kernel

.PHONY: mosslibc
mosslibc:
	$(MAKE) -C mosslibc

$(IMAGE_NAME).iso: $(LIMINE) kernel
	./tools/build-iso.sh

# $(IMAGE_NAME).hdd: $(LIMINE) kernel
# 	rm -f $(IMAGE_NAME).hdd
# 	dd if=/dev/zero bs=1M count=0 seek=64 of=$(IMAGE_NAME).hdd
# 	sgdisk $(IMAGE_NAME).hdd -n 1:2048 -t 1:ef00
# 	./$(LIMINE)/limine bios-install $(IMAGE_NAME).hdd
# 	mformat -i $(IMAGE_NAME).hdd@@1M
#
# 	mmd -i $(IMAGE_NAME).hdd@@1M ::/EFI ::/EFI/BOOT ::/boot ::/boot/limine
#
# 	mcopy -i $(IMAGE_NAME).hdd@@1M $(BUILDDIR)/bin/moss ::/boot
# 	mcopy -i $(IMAGE_NAME).hdd@@1M limine.cfg $(LIMINE)/limine-bios.sys ::/boot/limine
# 	mcopy -i $(IMAGE_NAME).hdd@@1M $(LIMINE)/BOOTX64.EFI ::/EFI/BOOT
# 	mcopy -i $(IMAGE_NAME).hdd@@1M $(LIMINE)/BOOTIA32.EFI ::/EFI/BOOT

.PHONY: clean
clean:
	rm $(SYSROOT)/boot/moss
	rm -rf $(IMAGE_NAME).iso $(IMAGE_NAME).hdd
	$(MAKE) -C kernel clean

.PHONY: distclean
distclean: clean
	rm -r $(SYSROOT)/boot/limine/
	rm -rf $(LIMINE) $(OVMF)
