#include "kprint.h"

struct PageDirectoryEntry {
  enum Flags {
    PRESENT  = 1<<0,
    WRITABLE = 1<<1,
    USER     = 1<<2,
    WRITE_THROUGH = 1<<3,
    CACHE_DISABLED = 1<<4,
    ACCESSED = 1<<5,
    ZERO = 1<<6,
    PAGE_SIZE = 1<<7,   // True if 4mb pages.
    GLOBAL = 1<<8,
  };
  uint32_t entry;
  PageDirectoryEntry() {
    entry = WRITABLE | WRITE_THROUGH | PAGE_SIZE | PRESENT;
  }
  void SetAddress(uint32_t addr) {
    entry = ((addr & 0x3ff) << 22) | (entry & 0xfff);
  }
};
