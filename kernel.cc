#include <stdint.h>
#include "screen.h"
#include "kprint.h"

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
    kprint(i->size, "->", (uint32_t) i->addr, ":", (uint32_t) i->len, ":", i->type, '\n');
  }
}

extern "C" void kmain(uint32_t magic, Multiboot* mb) {
  g_screen()->Clear();
  kprint("magic: ", Hex(magic), "\n");
  kprint("flags: ", Binary(mb->flags), "\n");
  kprint("mem_lower: ", mb->mem_lower, "\n");
  kprint("mem_upper: ", mb->mem_upper, "\n");
  kprint("mmap_length: ", mb->mmap_length, "\n");
  kprint("mmap_addr: ", mb->mmap_addr, "\n");

  PrintMemMap(mb->mmap_length, (mmap_entry*) mb->mmap_addr);

  while (1);
}
