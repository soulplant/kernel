#include "idt.h"
#include "isr.h"

Idt::Idt()
  : idtr_{0},
    idt_{{0}} {
  idtr_.limit = sizeof(idt_) - 1;
  idtr_.base = (uint32_t) &idt_[0];
  for (int i = 0; i < I86_MAX_INTERRUPTS; i++)
    idt_[i].SetInterruptHandler(IsrIgnore);

  idt_[0].SetInterruptHandler(Isr0);
  idt_[1].SetInterruptHandler(Isr1);
  idt_[2].SetInterruptHandler(Isr2);
  idt_[3].SetInterruptHandler(Isr3);
  idt_[4].SetInterruptHandler(Isr4);
  idt_[5].SetInterruptHandler(Isr5);
  idt_[6].SetInterruptHandler(Isr6);
  idt_[7].SetInterruptHandler(Isr7);
  idt_[8].SetInterruptHandler(Isr8);
  idt_[9].SetInterruptHandler(Isr9);
  idt_[10].SetInterruptHandler(Isr10);
  idt_[11].SetInterruptHandler(Isr11);
  idt_[12].SetInterruptHandler(Isr12);
  idt_[13].SetInterruptHandler(Isr13);
  idt_[14].SetInterruptHandler(Isr14);
  idt_[15].SetInterruptHandler(Isr15);
  idt_[16].SetInterruptHandler(Isr16);
  idt_[17].SetInterruptHandler(Isr17);
  idt_[18].SetInterruptHandler(Isr18);
  idt_[19].SetInterruptHandler(Isr19);
  idt_[20].SetInterruptHandler(Isr20);
  idt_[21].SetInterruptHandler(Isr21);
  idt_[22].SetInterruptHandler(Isr22);
  idt_[23].SetInterruptHandler(Isr23);
  idt_[24].SetInterruptHandler(Isr24);
  idt_[25].SetInterruptHandler(Isr25);
  idt_[26].SetInterruptHandler(Isr26);
  idt_[27].SetInterruptHandler(Isr27);
  idt_[28].SetInterruptHandler(Isr28);
  idt_[29].SetInterruptHandler(Isr29);
  idt_[30].SetInterruptHandler(Isr30);
  idt_[31].SetInterruptHandler(Isr31);

  idt_[33].SetInterruptHandler(KeyboardIsr);
}
