[bits 32]

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
  mov ax, 0x10
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  lgdt [GDT_toc]
  mov esp, stack_top
  push ebx
  push eax
  call kmain
  jmp $

GDT_start:
  ; null selector (reserved by processor)
  dd 0
  dd 0

  ; code selector
  dw 0xffff     ; Limit 0-15
  dw 0x0        ; Base 0-15
  db 0x0        ; Base 16-23
  db 10011010b  ; See http://www.brokenthorn.com/Resources/OSDev8.html
  db 11001111b  ; As above.
  db 0x0        ; Base 24-31

  ; data selector - as above but with the code/data bit set to 0
  dw 0xffff
  dw 0x0
  db 0x0
  db 10010010b  ; bit 3 here is 0, not 1 as above
  db 11001111b
  db 0x0

  ; null selector (reserved by processor)
  dd 0
  dd 0
  ; null selector (reserved by processor)
  dd 0
  dd 0
GDT_end:

GDT_toc:
  dw GDT_end - GDT_start - 1    ; size of GDT - 1
  dd GDT_start
