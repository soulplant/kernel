#ifndef KPRINT_H_
#define KPRINT_H_

#include "screen.h"

template<class T>
void kprint(T t);

template<class X, class Y, class... T>
void kprint(X x, Y y, T... args) {
  kprint(x);
  kprint(y, args...);
}

struct Binary {
  Binary(int value) : value(value) {}
  int value;
};

struct Hex {
  Hex(int value) : value(value) {}
  int value;
};

template<>
void kprint(char c);

template<>
void kprint(const char* str);

template<>
void kprint(char* str);

template<>
void kprint(int n);

template<>
void kprint(unsigned int n);

template<>
void kprint(Binary b);

template<>
void kprint(Hex b);

template<>
void kprint(bool b);

template<class... T>
void kprintln(T... args) {
  kprint(args...);
  kprint('\n');
}

#endif  // KPRINT_H_
