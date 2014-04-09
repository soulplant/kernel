// Called before and after trying to initialize a static variable in
// a function.
extern "C" bool __cxa_guard_acquire() {return true;}
extern "C" bool __cxa_guard_release() {return true;}

#include "screen.h"

int x = 0;

template<class T>
void kprint(T t);

template<class X, class Y, class... T>
void kprint(X x, Y y, T... args) {
  kprint(x);
  kprint(y, args...);
}

template<>
void kprint(char c) {
  g_screen()->PrintChar(c);
}

template<>
void kprint(const char* str) {
  while (*str) {
    kprint(*str);
    str++;
  }
}

template<>
void kprint(char* str) {
  kprint((const char*) str);
}

template<>
void kprint(int n) {
  char buf[32];
  int i;
  bool sign = false;
  if (n < 0) {
    sign = true;
    n = -n;
  }
  for (i = 0; n > 0 || i == 0; i++) {
    buf[i] = (n % 10)["0123456789"];
    n /= 10;
  }
  buf[i] = 0;
  for (int y = 0; y < i / 2; y++) {
    char temp = buf[y];
    buf[y] = buf[i - 1 - y];
    buf[i - 1 - y] = temp;
  }
  if (sign)
    kprint('-');
  kprint(&buf[0]);
}

static char memory[1024];
static char* mem = memory;

void* operator new(unsigned int s) {
  char* result = mem;
  mem += s;
  return result;
}

void operator delete(void *) {
}

extern "C" void kmain() {
  g_screen()->Clear();
  kprint('a', 0, "hi there", 'c', 'd');
  kprint(-1, 0, 1, 12);
  while (1);
}
