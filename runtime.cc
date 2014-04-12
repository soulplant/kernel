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

static char* mem = (char*) (1024*1024);

// TODO(koz): Don't leak everything.
void* operator new(unsigned int s) {
  char* result = mem;
  mem += s;
  kprintln("allocating ", s, " bytes at ", (uint32_t) result);
  return result;
}

void operator delete(void*) {
  // TODO
}

void* operator new[](unsigned int s) {
  void* mem = operator new(s + sizeof(unsigned int));
  unsigned int* m = (unsigned int*) mem;
  m[0] = s;
  char* result = (char*) mem;
  return (void*) (result + sizeof(unsigned int));
}

void operator delete[](void* p) {
  // TODO
}

void* memmove(void* dest, const void* src, size_t n) {
  if (dest < src) {
  }
}
