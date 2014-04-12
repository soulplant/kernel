#ifndef KPRINT_H_
#define KPRINT_H_

#include "screen.h"

void kprint();
template<class T, class... Args>
void kprint(const T& t, const Args&... args);

struct Binary {
  Binary(int value) : value(value) {}
  int value;
};

struct Hex {
  Hex(int value) : value(value) {}
  int value;
};

template<class T> struct printer;

template<>
struct printer<char> {
  static void print(char c) {
    g_screen()->PrintChar(c);
  }
};

template<>
struct printer<const char*> {
  static void print(const char* str) {
    while (*str) {
      kprint(*str++);
    }
  }
};

template<class T>
struct printer<T*> {
  static void print(const T* str) {
    kprint(str);
  }
};

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
struct printer<int> {
  static void print(int n) {
    print_base(n, 10);
  }
};

template<>
struct printer<unsigned int> {
  static void print(unsigned int n) {
    printer<int>::print(n);
  }
};

template<>
struct printer<bool> {
  static void print(bool b) {
    print(b ? '1' : '0');
  }
};

template<class T, int N>
struct printer<T[N]> {
  static void print(const T ts[N]) {
    for (int i = 0; i < N; i++)
      kprint(ts[i]);
  }
};

template<int N>
struct printer<char[N]> {
  static void print(const char ts[N]) {
    kprint(&ts[0]);
  }
};

template<>
struct printer<Binary> {
  static void print(const Binary& b) {
    print_base(b.value, 2);
  }
};

template<>
struct printer<Hex> {
  static void print(const Hex& b) {
    print_base(b.value, 16);
  }
};

template<class T, class... Args>
void kprint(const T& t, const Args&... args) {
  printer<T>::print(t);
  kprint(args...);
}

template<class... T>
void kprintln(const T&... args) {
  kprint(args...);
  kprint('\n');
}

#endif  // KPRINT_H_
