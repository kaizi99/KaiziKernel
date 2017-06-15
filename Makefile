GPPPARAMS = -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = start.o kernel.o terminal.o

%.o: %.c
	gcc $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

test: clean mykernel.bin 
	qemu-system-i386 -kernel mykernel.bin

clean:
	rm *.o mykernel.bin