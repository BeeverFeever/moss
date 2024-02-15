KERNEL := kernel

DEFAULT_CC := cc
DEFAULT_LD := ld
DEFAULT_CFLAGS := -g -O2 -pipe
DEFAULT_CPPFLAGS :=
DEFAULT_FASMFLAGS := -F dwarf -g
DEFAULT_LDFLAGS :=

BUILDDIR := ./build

CFLAGS += \
    -Wall \
    -Wextra \
    -std=gnu11 \
    -ffreestanding \
    -fno-stack-protector \
    -fno-stack-check \
    -fno-lto \
    -fPIE \
    -m64 \
    -march=x86-64 \
    -mno-80387 \
    -mno-mmx \
    -mno-sse \
    -mno-sse2 \
    -mno-red-zone

# Internal C preprocessor flags that should not be changed by the user.
CPPFLAGS := \
	-include ../mosslibc/mossdefines.h \
	-Isrc \
	-I../extern \
	-isystem ../mosslibc \
    $(CPPFLAGS) \
    -MMD \
    -MP

# Internal linker flags that should not be changed by the user.
LDFLAGS += \
    -m elf_x86_64 \
    -nostdlib \
    -static \
    -pie \
    --no-dynamic-linker \
    -z text \
    -z max-page-size=0x1000 \
    -T linker.ld

FASMFLAGS += \
    -Wall \
    -f elf64

# Use "find" to glob all *.c, *.S, and *.asm files in the tree and obtain the
# object and header dependency file names.
CFILES := $(shell cd src && find -L * -type f -name '*.c')
ASFILES := $(shell cd src && find -L * -type f -name '*.S')
FASMFILES := $(shell cd src && find -L * -type f -name '*.asm')
OBJ := $(addprefix $(BUILDDIR)/obj/,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o) $(FASMFILES:.asm=.asm.o))
HEADER_DEPS := $(addprefix $(BUILDDIR)/obj/,$(CFILES:.c=.c.d) $(ASFILES:.S=.S.d))

# Default target.
.PHONY: all
all: $(BUILDDIR)/bin/$(KERNEL)

# extern/limine.h:
# 	curl -Lo $@ https://github.com/limine-bootloader/limine/raw/trunk/limine.h

# Link rules for the final kernel executable.
$(BUILDDIR)/bin/$(KERNEL): makefile linker.ld $(OBJ)
	mkdir -p "$$(dirname $@)"
	$(LD) $(OBJ) $(LDFLAGS) -o $@

# Include header dependencies.
-include $(HEADER_DEPS)

# Compilation rules for *.c files.
$(BUILDDIR)/obj/%.c.o: src/%.c makefile # bootloader/limine.h
	mkdir -p "$$(dirname $@)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Compilation rules for *.S files.
$(BUILDDIR)/obj/%.S.o: src/%.S makefile
	mkdir -p "$$(dirname $@)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Compilation rules for *.asm (fasm) files.
$(BUILDDIR)/obj/%.asm.o: src/%.asm makefile
	mkdir -p "$$(dirname $@)"
	fasm $(FASMFLAGS) $< -o $@

# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf $(BUILDDIR)

.PHONY: distclean
distclean: clean
	# rm -f bootloader/limine.h
