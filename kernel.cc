#include "screen.h"
#include "kprint.h"

extern "C" void kmain() {
  g_screen()->Clear();
  kprint('a', 0, "hi there", 'c', 'd');
  kprint(-1, 0, 1, 12);
  while (1);
}
