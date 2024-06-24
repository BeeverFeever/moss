KERNEL := moss

COMPILER := ../tools/path/bin/x86_64-moss-gcc
LINKER := ../tools/path/bin/x86_64-moss-ld
ASSEMBLER := nasm
BUILDDIR := ./build

CFLAGS := -std=c23 -g -c \
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
			 -mno-red-zone

FASMFLAGS := -f elf64

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

OBJS := $(addprefix $(BUILDDIR)/obj/,$(CFILES:.c=.o) $(FASMFILES:.asm=.asm.o))

.PHONY: all
all: $(BUILDDIR)/bin/$(KERNEL)

$(BUILDDIR)/bin/$(KERNEL): linker.ld $(OBJS)
	mkdir -p "$$(dirname $@)"
	$(LINKER) $(OBJS) $(LDFLAGS) -o $@

$(BUILDDIR)/obj/%.o: src/%.c 
	mkdir -p "$$(dirname $@)"
	$(COMPILER) $(CFLAGS) $< -o $@

$(BUILDDIR)/obj/%.asm.o: src/%.asm
	mkdir -p "$$(dirname $@)"
	$(ASSEMBLER) $(FASMFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
