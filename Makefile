CC=i386-elf-gcc
AS=i386-elf-as
LD=i386-elf-ld

GPPPARAMS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude

CSOURCES  = $(wildcard **/*.c)
ASSOURCES = $(wildcard **/*.s)
OBJECTS   = $(CSOURCES:.c=.o)
OBJECTS   += $(ASSOURCES:.s=.o)

KERNEL = kaizikernel.bin

all: $(OBJECTS )$(KERNEL)

%.o: %.c
	$(CC) $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	$(AS) -o $@ $<

$(KERNEL): $(OBJECTS)
	$(LD) -T linker.ld -o $@ $(OBJECTS)

.PHONY: test
test: $(KERNEL)
	qemu-system-i386 -kernel $(KERNEL)

.PHONY: clean
clean:
	rm -rf $(OBJECTS) 
	rm -rf $(KERNEL)