#include "stdint.h"

#define I86_MAX_INTERRUPTS 256

#define PACKED __attribute__((__packed__))

struct PACKED IdtDescriptor {
  uint16_t baseLo;
  uint16_t sel;
  uint8_t reserved;
  uint8_t flags;
  uint16_t baseHi;
  void SetInterruptHandler(void (*handler)()) {
    uint32_t addr = (uint32_t)handler;
    baseLo = addr & 0xffff;
    baseHi = (addr >> 16) & 0xffff;
    sel = 0x8;
    reserved = 0;
    flags = 0x8e;
  }
};

struct PACKED Idtr {
  uint16_t limit;
  uint32_t base;
};

extern "C" void LoadIdt(uint32_t idtr);

class Idt {
 public:
  Idt();

  IdtDescriptor& operator[](int i) {
    return idt_[i];
  }

  void Load() {
    // LoadIdt(&idtr_);
    uint32_t idtr = (uint32_t) &idtr_;
    asm("lidt (%0);" :: "r"(idtr));
  }

  Idtr idtr_;
  IdtDescriptor idt_[I86_MAX_INTERRUPTS];
};
