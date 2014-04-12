#include "kprint.h"

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

namespace {
void print_base(int n, int base) {
  char buf[32];
  int i;
  bool sign = false;
  if (n < 0) {
    sign = true;
    n = -n;
  }
  for (i = 0; n > 0 || i == 0; i++) {
    buf[i] = (n % base)["0123456789abcdef"];
    n /= base;
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
}

template<>
void kprint(int n) {
  print_base(n, 10);
}

template<>
void kprint(unsigned int n) {
  kprint((int) n);
}

template<>
void kprint(Binary b) {
  print_base(b.value, 2);
}

template<>
void kprint(Hex b) {
  print_base(b.value, 16);
}

template<>
void kprint(bool b) {
  kprint(b ? '1' : '0');
}
