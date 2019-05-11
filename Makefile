CSRC=$(shell find ./ -iname *.c)
COBJ=$(foreach obj, $(CSRC:./%.c=%.o), obj/$(obj))
ASRC=$(shell find ./ -name *.s)
GASSRC=$(shell find ./ -name *.S)
AOBJ=$(foreach obj, $(ASRC:./%.s=%_s.o), obj/$(obj))
GASOBJ=$(foreach obj, $(GASSRC:./%.S=%_S.o), obj/$(obj))
OBJ=$(COBJ) $(AOBJ) $(GASOBJ)
HEADERS=$(shell find -iname *.h)
INCLUDE=$(foreach path, $(HEADERS), -I$(dir $(path)))
FLAGS=-pedantic --std=gnu99 -O0 -ffreestanding -fbuiltin -Wall -Wextra -nostdlib -lgcc -g3
INCLUDE=-I./src/drivers/keyboard -I./src/drivers/pit/ -I./src/descriptors/pic/ -I./src/ -I./src/descriptors/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/vga/ -I./src/common/ -I./src/descriptors/ -I./src/libc/string/ -I./src/vga/ -I./src/descriptors/

CC=i686-elf-gcc
AS=nasm
COMPILE_COMMAND=-c $< -o $@
OUTPUT=kernel.bin
LINK_COMMAND=-T./src/linker.ld -o $(OUTPUT)
ISODIR=grub
OUTCOPYDIR=$(ISODIR)/boot/
BOCHS=$(HOME)/.installed/bin/bochs


obj/%_S.o: %.S
	-mkdir -p $(dir $@)
	i686-elf-as $< -o $@

obj/%_s.o: %.s
	-mkdir -p $(dir $@)
	$(AS) -felf32 $< -o $@

obj/%.o: %.c
	-mkdir -p $(dir $@)
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)


all: $(OBJ)
	$(CC) $(OBJ) $(FLAGS) $(LINK_COMMAND)

TAGS: $(SRC) Makefile
	cd src;\
	ctags -e -R;\
	cd ..

geniso:	all
	cp $(OUTPUT) $(ISODIR)/boot/$(OUTPUT)
	grub-mkrescue -o $(OUTPUT:.bin=.iso) $(ISODIR)
runbochs:
	$(BOCHS) -f bochsrc -q

clean:
	-rm obj/* -rf


test:
	echo $(CSRC)
	echo $(ASRC)
	echo $(GASSRC)
	echo $(COBJ)
	echo $(AOBJ)
	echo $(GASOBJ)
	echo $(INCLUDE)




