CC=i386-elf-gcc
AS=i386-elf-as
LD=i386-elf-ld

GPPPARAMS = -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASPARAMS = --32

objects = start.o kernel.o terminal.o

out = kaizikernel.bin

%.o: %.c
	$(CC) $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	$(AS) $(ASPARAMS) -o $@ $<

$(out): linker.ld $(objects)
	$(LD) -T $< -o $@ $(objects)

.PHONY: test
test: clean $(out)
	qemu-system-i386 -kernel $(out)

.PHONY: clean
clean:
	rm -rf *.o mykernel.bin
