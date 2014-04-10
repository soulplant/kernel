#include <stdint.h>
#include <stddef.h>
#include "screen.h"

Screen::Screen()
    : Screen((char*) 0xb8000) {}

Screen::Screen(char* memory)
    : memory_(memory),
      x_(0),
      y_(0) {
  static int count = 0;
  count++;
  memory_[(count + 10) * 2] = 'a';
}

void Screen::PrintChar(char c) {
  if (c == '\n') {
    x_ = 0;
    y_++;
    return;
  }
  memory_[(y_ * kScreenWidth + x_) * 2] = c;
  x_++;
  if (x_ >= kScreenWidth) {
    x_ = 0;
    y_ ++;
    if (y_ >= kScreenHeight) {
      y_ = kScreenHeight - 1;
      ScrollUp();
    }
  }
}

void Screen::Clear() {
  for (int y = 0; y < 24; y++) {
    for (int x = 0; x < 80; x++) {
      memory_[(y * 80 + x) * 2] = ' ';
    }
  }
  x_ = 0;
  y_ = 0;
}

void Screen::ScrollUp() {
  // TODO:
}

Screen* g_screen() {
  static Screen screen;
  return &screen;
}
