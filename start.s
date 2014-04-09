# [bits 32]

global start

MODULEALIGN equ 1<<0
MEMINFO     equ 1<<1
FLAGS       equ MODULEALIGN | MEMINFO
MAGIC       equ 0x1badb002
CHECKSUM    equ -(MAGIC + FLAGS)

section .multiboot
align 4
MultiBootHeader:
  dd MAGIC
  dd FLAGS
  dd CHECKSUM

section .bootstrap_stack nobits
align 4
stack_bottom:
  resb 16384
stack_top:

section .text:
align 4

extern kmain

start:
  mov esp, stack_top
  mov [0xb8000], byte 67
  call kmain
  jmp $
