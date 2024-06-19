KERNEL := moss

CC := ../tools/path/bin/x86_64-moss-gcc
LD := ../tools/path/bin/x86_64-moss-ld
BUILDDIR := ./build

CFLAGS := -g -c \
			 -include ../mosslib/include/mosscommon.h \
			 -Isrc \
			 -I../extern \
			 -Wall \
			 -Wextra \
			 -ffreestanding \
			 -fno-stack-protector \
			 -fno-stack-check \
			 -fno-lto \
			 -fPIE \
			 -fcommon \
			 -nostartfiles \
			 -nostdlib \
			 -m64 \
			 -mno-mmx \
			 -mno-80387 \
			 -mno-sse \
			 -mno-sse2 \
			 -mno-red-zone

FASMFLAGS := -F dwarf -g \
    -Wall \
    -f elf64

LDFLAGS := \
    -m elf_x86_64_moss \
    -nostdlib \
    -static \
    -pie \
    --no-dynamic-linker \
    -z text \
    -z max-page-size=0x1000 \
    -T linker.ld

CFILES := $(shell cd src && find -L * -type f -name '*.c')
FASMFILES := $(shell cd src && find -L * -type f -name '*.asm')

OBJ := $(addprefix $(BUILDDIR)/obj/,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o) $(FASMFILES:.asm=.asm.o))
HEADER_DEPS := $(addprefix $(BUILDDIR)/obj/,$(CFILES:.c=.c.d) $(ASFILES:.S=.S.d))

# Default target.
.PHONY: all
all: $(BUILDDIR)/bin/$(KERNEL)

# extern/limine.h:
# 	curl -Lo $@ https://github.com/limine-bootloader/limine/raw/trunk/limine.h

# Link rules for the final kernel executable.
$(BUILDDIR)/bin/$(KERNEL): linker.ld $(OBJ)
	mkdir -p "$$(dirname $@)"
	$(LD) $(OBJ) $(LDFLAGS) -o $@

$(BUILDDIR)/obj/%.c.o: src/%.c # bootloader/limine.h
	mkdir -p "$$(dirname $@)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/obj/%.asm.o: src/%.asm
	mkdir -p "$$(dirname $@)"
	fasm $(FASMFLAGS) $< -o $@

# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
