ENTRY (start)

SECTIONS {
  . = 0x100000;

  .text : {
    /* *(.multiboot) */
    *(.text)
  }

  .rodata ALIGN (0x1000) : {
    *(.rodata)
  }

  .data ALIGN (0x1000) : {
    *(.data)
  }

  .bss BLOCK(4K) : ALIGN(4K) {
    bss_start = .;
    *(COMMON)
    *(.bss)
    *(.bootstrap_stack)
    bss_end = .;
  }
}
