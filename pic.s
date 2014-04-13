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

  ; 8086 mode for both
  mov al, 0x1
  out PIC1CTL, al
  out PIC2CTL, al

  ; mask on all interrupts
  mov al, 0x0
  out PIC1CTL, al
  out PIC2CTL, al
  ret
