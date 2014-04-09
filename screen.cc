#include "screen.h"

Screen::Screen()
    : Screen((char*) 0xb8000) {}
Screen::Screen(char* memory)
    : memory_(memory) {}

void Screen::PrintChar(char c) {
  memory_[x_ * 2] = c;
  x_++;
}

void Screen::Clear() {
  for (int y = 0; y < 24; y++) {
    for (int x = 0; x < 80; x++) {
      memory_[(y * 80 + x) * 2] = ' ';
    }
  }
}

Screen* g_screen() {
  static Screen screen;
  return &screen;
}
