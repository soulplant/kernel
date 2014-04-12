#include <stdint.h>
#include "screen.h"
#include "kprint.h"
#include "vector.h"

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

template<class T>
void PrintVector(Vector<T>& v) {
  kprint("[");
  bool first = true;
  for (int i = 0; i < v.size(); i++) {
    if (!first)
      kprint(", ");
    first = false;
    kprint(v[i]);
  }
  kprintln("]");
}

extern "C" void kmain(uint32_t magic, Multiboot* mb) {
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

  Vector<int> v;
  v.push_back(3);
  v.emplace_back(4);
  v.emplace_back(5);
  v.erase(1);
  v.erase(1);
  // kprintln(v);
  // kprintln("int:", v[0]);
  // kprintln("size:", v.size());
  // kprint("int:", v[1], "\n");

  while (1);
}
