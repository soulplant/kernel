#include <stdint.h>
#include "screen.h"
#include "kprint.h"
#include "vector.h"
#include "idt.h"

struct Multiboot {
  uint32_t flags;
  uint32_t mem_lower;
  uint32_t mem_upper;
  uint32_t boot_device;
  uint32_t cmd_line;

  uint32_t mods_count;
  uint32_t mods_addr;
  uint32_t syms[4];
  uint32_t mmap_length;
  uint32_t mmap_addr;
};

struct mmap_entry {
  uint32_t size;
  uint64_t addr;
  uint64_t len;
  uint32_t type;
};

void PrintMemMap(uint32_t length, mmap_entry* entry) {
  for (mmap_entry* i = entry;
       ((uint32_t) i) < ((uint32_t) entry) + length;
       i = (mmap_entry*) (((uint32_t) i) + i->size + sizeof(i->size))) {
    kprintln(i->size, "->", (uint32_t) i->addr, ":", (uint32_t) i->len, ":", i->type);
  }
}

extern "C" void SetupPic();

struct InterruptInfo {
  uint32_t int_no;
  uint32_t err_code;
};

static uint32_t x = 0;
static uint32_t o = 0;

extern "C" void OnInterrupt(InterruptInfo info) {
  x++;
  o = info.int_no;
}

extern "C" void OnKeyboardInterrupt(uint32_t scancode) {
  kprintln("keyboard: ", Hex(scancode), "(", x, ", ", o, ")");
}

extern "C" void kmain(uint32_t magic, Multiboot* mb) {
  SetupPic();
  Idt idt;
  idt.Load();
  asm("sti");

  g_screen()->Clear();
  int x[] = {1,2,3,4,5};
  kprintln(x);
  kprintln("magic: ", Hex(magic));
  kprintln("flags: ", Binary(mb->flags));
  kprintln("mem_lower: ", mb->mem_lower);
  kprintln("mem_upper: ", mb->mem_upper);
  kprintln("mmap_length: ", mb->mmap_length);
  kprintln("mmap_addr: ", mb->mmap_addr);

  PrintMemMap(mb->mmap_length, (mmap_entry*) mb->mmap_addr);

  while (1);
}
