SRC=./src/drivers/pit/pit.c ./src/drivers/pit/pit_s.s ./src/descriptors/pic/pic_s.s ./src/libc/string/strcat.c ./src/libc/string/strcmp.c ./src/libc/string/strcoll.c ./src/libc/string/memset.c ./src/libc/string/strchr.c ./src/libc/string/strcpy.c ./src/libc/string/index.c ./src/libc/string/stpcpy.c ./src/libc/string/memcpy.c ./src/libc/string/strlen.c ./src/libc/string/strcasecmp.c ./src/descriptors/interrupts.c ./src/descriptors/idt.c ./src/descriptors/gdt.c ./src/vga/vga.c ./src/kernel.c ./src/descriptors/lgdt.s ./src/descriptors/interrupts.s ./src/descriptors/lidt.s ./src/start.S
OBJ=./obj/drivers/pit/pit.o ./obj/drivers/pit/pit_s.o ./obj/descriptors/pic/pic_s.o ./obj/libc/string/strcat.o ./obj/libc/string/strcmp.o ./obj/libc/string/memset.o ./obj/libc/string/strcoll.o ./obj/libc/string/strchr.o ./obj/libc/string/strcpy.o ./obj/libc/string/index.o ./obj/libc/string/stpcpy.o ./obj/libc/string/memcpy.o ./obj/libc/string/strlen.o ./obj/libc/string/strcasecmp.o ./obj/descriptors/interrupts.o ./obj/descriptors/idt.o ./obj/descriptors/gdt.o ./obj/vga/vga.o ./obj/kernel.o ./obj/descriptors/lgdt.o ./obj/descriptors/interrupts_s.o ./obj/descriptors/lidt.o ./obj/start.o
FLAGS=-pedantic --std=gnu99 -O0 -ffreestanding -fbuiltin -Wall -Wextra -nostdlib -lgcc -g3
INCLUDE=-I./src/drivers/pit/ -I./src/descriptors/pic/ -I./src/ -I./src/descriptors/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/libc/string/ -I./src/vga/ -I./src/common/ -I./src/descriptors/ -I./src/libc/string/ -I./src/vga/ -I./src/descriptors/

CC=i686-elf-gcc
COMPILE_COMMAND=-c $< -o $@
OUTPUT=kernel.bin
LINK_COMMAND=-T./src/linker.ld -o $(OUTPUT)
ISODIR=grub
OUTCOPYDIR=$(ISODIR)/boot/



./obj/libc/string/strcat.o: ./src/libc/string/strcat.c
	-mkdir -p ./obj/libc/string
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)



./obj/libc/string/strcmp.o: ./src/libc/string/strcmp.c
	-mkdir -p ./obj/libc/string
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)



./obj/libc/string/strcoll.o: ./src/libc/string/strcoll.c
	-mkdir -p ./obj/libc/string
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)


./obj/libc/string/strchr.o: ./src/libc/string/strchr.c
	-mkdir -p ./obj/libc/string
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)



./obj/libc/string/strcpy.o: ./src/libc/string/strcpy.c
	-mkdir -p ./obj/libc/string
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)



./obj/libc/string/index.o: ./src/libc/string/index.c
	-mkdir -p ./obj/libc/string
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)



./obj/libc/string/stpcpy.o: ./src/libc/string/stpcpy.c
	-mkdir -p ./obj/libc/string
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)



./obj/libc/string/memcpy.o: ./src/libc/string/memcpy.c
	-mkdir -p ./obj/libc/string
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)

./obj/libc/string/memset.o: ./src/libc/string/memset.c
		-mkdir -p ./obj/libc/string
		$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)


./obj/libc/string/strlen.o: ./src/libc/string/strlen.c
	-mkdir -p ./obj/libc/string
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)



./obj/libc/string/strcasecmp.o: ./src/libc/string/strcasecmp.c
	-mkdir -p ./obj/libc/string
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)



./obj/descriptors/interrupts.o: ./src/descriptors/interrupts.c
	-mkdir -p ./obj/descriptors
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)



./obj/descriptors/idt.o: ./src/descriptors/idt.c
	-mkdir -p ./obj/descriptors
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)



./obj/descriptors/gdt.o: ./src/descriptors/gdt.c
	-mkdir -p ./obj/descriptors
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)



./obj/vga/vga.o: ./src/vga/vga.c
	-mkdir -p ./obj/vga
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)



./obj/kernel.o: ./src/kernel.c
	-mkdir -p ./obj
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)



./obj/descriptors/lgdt.o: ./src/descriptors/lgdt.s
	-mkdir -p ./obj/descriptors
	nasm -felf32 $< -o $@



./obj/descriptors/interrupts_s.o: ./src/descriptors/interrupts.s
	-mkdir -p ./obj/descriptors
	nasm -felf32 $< -o $@



./obj/descriptors/lidt.o: ./src/descriptors/lidt.s
	-mkdir -p ./obj/descriptors
	nasm -felf32 $< -o $@


./obj/start.o: ./src/start.S
	-mkdir -p ./obj
	i686-elf-as $< -o $@

./obj/descriptors/pic/pic_s.o: ./src/descriptors/pic/pic_s.s
	-mkdir -p ./obj/descriptors/pic
	nasm -felf32 $< -o $@

./obj/drivers/pit/pit.o: ./src/drivers/pit/pit.c
	-mkdir -p ./obj/drivers/pit/
	$(CC) $(COMPILE_COMMAND) $(FLAGS) $(INCLUDE)

./obj/drivers/pit/pit_s.o: ./src/drivers/pit/pit_s.s
	-mkdir -p ./obj/drivers/pit
	nasm -felf32 $< -o $@

all: $(OBJ)
	$(CC) $(OBJ) $(FLAGS) $(LINK_COMMAND)

geniso:	all
	cp $(OUTPUT) $(ISODIR)/boot/$(OUTPUT)
	grub-mkrescue -o $(OUTPUT:.bin=.iso) $(ISODIR)

clean:
	-rm obj/* -rf
