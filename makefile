# Compiler for building the 'limine' executable for the host.
CC := ~/software/cross-gcc/bin/x86_64-elf-gcc
LD := ld.lld

OS_NAME := moss
BUILDDIR := build
ISO := $(BUILDDIR)/bin/$(OS_NAME).iso

ASSEMBLER := nasm
NASMFLAGS := -F dwarf -g -f elf64
FASMFLAGS :=

ASMFLAGS := $(NASMFLAGS)

CFLAGS := \
    -Wall \
    -Wextra \
    -std=gnu11 \
    -ffreestanding \
    -fno-stack-protector \
    -fno-stack-check \
    -fno-lto \
    -fPIE \
	-fPIC \
    -m64 \
    -march=x86-64 \
    -mabi=sysv \
    -mno-80387 \
    -mno-mmx \
    -mno-sse \
    -mno-sse2 \
    -mno-red-zone \
	-MMD \
	-MP \
	-nostdinc \
  	-Isrc \
	-Iinclude \
	-Iextern

LDFLAGS =         			\
    -nostdlib               \
    -static                 \
    -m elf_x86_64           \
    -z max-page-size=0x1000 \
    -z text 				\
    -T resources/linker.ld  \
	-no-pie					\
	--no-dynamic-linker

QEMUFLAGS := -smp 2 -m 2G -monitor stdio -serial file:moss.log -vga std

CFILES := $(shell find ./src -type f -name "*.c") extern/flanterm/flanterm.c extern/flanterm/backends/fb.c
ASMFILES := $(shell find ./src -type f -name "*.asm")
OBJS := $(addprefix $(BUILDDIR)/obj/,$(CFILES:.c=.c.o) $(ASMFILES:.asm=.asm.o))

# $(info $$CFILES is [${CFILES}])

.PHONY: all
all: $(ISO)

.PHONY: uefi
uefi: extern/ovmf $(ISO)
	qemu-system-x86_64 -M q35 $(QEMUFLAGS) -bios extern/ovmf/OVMF.fd -cdrom $(ISO) -boot d

.PHONY: bios
bios: $(ISO)
	qemu-system-x86_64 -M q35 -m 2G -cdrom $(ISO) -boot d

.PHONY: ovmf
ovmf:
	@/usr/bin/printf "[\033[1;35mKernel - extern\033[0m] \033[32mGetting OVMF\n\033[0m"
	@mkdir -p extern/ovmf
	cd extern/ovmf && curl -Lo OVMF.fd https://retrage.github.io/edk2-nightly/bin/RELEASEX64_OVMF.fd

limine:
	@/usr/bin/printf "[\033[1;35mKernel - extern\033[0m] \033[32mBuilding Limine\n\033[0m"
	@$(MAKE) -C extern/limine

$(ISO): limine resources/limine.cfg $(BUILDDIR)/bin/$(OS_NAME).elf
	@/usr/bin/printf "[\033[1;35mKernel\033[0m] \033[32mBuilding ISO\n\033[0m"
	rm -rf $(dir $@)/iso_root
	mkdir -p $(dir $@)/iso_root

	cp 	$(BUILDDIR)/bin/$(OS_NAME).elf \
		resources/limine.cfg \
	   	extern/limine/limine-bios.sys extern/limine/limine-bios-cd.bin extern/limine/limine-uefi-cd.bin \
	   	$(dir $@)/iso_root

	mkdir -p $(dir $@)/iso_root/EFI/BOOT
	cp -v extern/limine/BOOTX64.EFI extern/limine/BOOTIA32.EFI $(dir $@)/iso_root/EFI/BOOT/

	xorriso -as mkisofs \
		-b limine-bios-cd.bin \
		-no-emul-boot \
		-boot-load-size 4 \
		-boot-info-table \
		--efi-boot limine-uefi-cd.bin \
		-efi-boot-part \
		--efi-boot-image \
		--protective-msdos-label \
		$(dir $@)/iso_root -o $@

	./extern/limine/limine bios-install $(ISO)
	rm -rf $(dir $@)/iso_root
	@/usr/bin/printf "[\033[1;35mKernel\033[0m] \033[32mISO built at \033[33m$@\n\033[0m"

# Link rules for the final kernel executable.
$(BUILDDIR)/bin/$(OS_NAME).elf: $(OBJS)
	@/usr/bin/printf "[\033[1;35mKernel\033[0m] \033[32mLinking \033[33m$@\n\033[0m"
	@mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) $^ -o $@ 

# Compilation rules for *.c files.
$(BUILDDIR)/obj/extern/%.c.o: extern/flanterm src/bootloader/limine.h
	@/usr/bin/printf "[\033[1;35mKernel\033[0m] \033[32mCompiling \033[33m$<\n\033[0m"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(shell echo "$@" | sed 's/build\/obj\///g' | sed 's/\.o//g') -o $@

# Compilation rules for *.c files.
$(BUILDDIR)/obj/./src/%.c.o: src/%.c extern/flanterm src/bootloader/limine.h
	@/usr/bin/printf "[\033[1;35mKernel\033[0m] \033[32mCompiling \033[33m$<\n\033[0m"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation rules for *.asm (fasm) files.
$(BUILDDIR)/obj/%.asm.o: %.asm
	@/usr/bin/printf "[\033[1;35mKernel\033[0m] \033[32mAssembling \033[33m$^\n\033[0m"
	@mkdir -p $(dir $@)
	$(ASSEMBLER) $(ASMFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
	$(MAKE) -C extern/limine clean
