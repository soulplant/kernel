#include <stddef.h>
#include <stdint.h>

#include "kprint.h"

// Called before and after trying to initialize a static variable in
// a function.
namespace {
bool HasRun(uint64_t* guard) {
  return *guard;
}

void SetRun(uint64_t* guard) {
  *guard = 1;
}
}

extern "C" int
__cxa_guard_acquire(uint64_t* guard) {
  if (!HasRun(guard)) {
    SetRun(guard);
    return true;
  }
  return false;
}
extern "C" void
__cxa_guard_release(uint64_t* guard) {
}

// Defined by the linker.
extern uint32_t bss_end;

static uint8_t* mem = (uint8_t*) &bss_end;

// TODO(koz): Don't leak everything.
void* operator new(unsigned int s) {
  kprintln("new(", s, ")");
  uint8_t* result = mem;
  mem += s;
  return result;
}

void operator delete(void*) {
  // TODO
}

void* operator new[](unsigned int s) {
  return operator new(s);
}

void operator delete[](void* p) {
  // TODO
}

void* memmove(void* dest, const void* src, size_t n) {
  if (dest < src) {
  }
}
