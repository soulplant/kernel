// Called before and after trying to initialize a static variable in
// a function.
extern "C" bool __cxa_guard_acquire() {return true;}
extern "C" bool __cxa_guard_release() {return true;}

static char memory[1024];
static char* mem = memory;

void* operator new(unsigned int s) {
  char* result = mem;
  mem += s;
  return result;
}

void operator delete(void *) {
}
