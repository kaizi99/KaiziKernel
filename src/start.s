.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
  .long MAGIC
  .long FLAGS
  .long CHECKSUM

.section .text

.extern kernelMain

.global start
start:
  mov $kernel_stack, %esp
  call kernelMain
hang:
  cli
  hlt
  jmp hang

.section .bss
.space 2*1024*1024; # 2MiB
kernel_stack:
