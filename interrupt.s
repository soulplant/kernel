; PIC.
PIC1 equ 0x20
PIC2 equ 0xA0
PIC1CTL equ 0x21
PIC2CTL equ 0xA1
global SetupPic

; By default the x86 has its interrupt and trap/exception handlers all mapped
; to the same interrupt handlers, so we remap the interrupts here from
; 0x0..0xf -> 0x20..0x2f.
SetupPic:
  ; ICW to both
  mov al, 0x11
  out PIC1, al
  out PIC2, al

  ; Set the IRQ bases - 32 and 40 respectively
  mov al, 0x20
  out PIC1CTL, al
  mov al, 0x28
  out PIC2CTL, al

  ; PIC1's slave address in unary (ie: 2)
  mov al, 0x4
  out PIC1CTL, al

  ; PIC2's master address in binary
  mov al, 0x2
  out PIC2CTL, al

  ; 8086 mode for both
  mov al, 0x1
  out PIC1CTL, al
  out PIC2CTL, al

  ; mask on all interrupts
  mov al, 0x0
  out PIC1CTL, al
  out PIC2CTL, al
  ret

; INTERRUPTS.
global LoadIdt
LoadIdt:
  pop eax
  lidt [eax]
  ret

%macro ISR_NOERRCODE 1
  global Isr%1
  Isr%1:
    cli
    push byte 0   ; push dummy error code
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
  global Isr%1
  Isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro

extern OnInterrupt
extern OnKeyboardInterrupt

global isr_common_stub
isr_common_stub:
  call OnInterrupt
  add esp, 8  ; pop the error code and int number.
  mov al, 0x20
  out 0x20, al  ; EOI
  out 0xA0, al  ; EOI
  sti
  iret

global IsrIgnore
IsrIgnore:
  mov al, 0x20
  out PIC1, al  ; EOI
  out PIC2, al  ; EOI
  sti
  iret

global KeyboardIsr
KeyboardIsr:
  xor eax, eax
  in al, 0x60
  push eax
  call OnKeyboardInterrupt
  ; pop eax
  mov al, 0x20
  out 0x20, al  ; EOI
  out 0xA0, al  ; EOI
  sti
  iret

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

