#include "vector.h"

template<class T>
void kprint(const Vector<T>& v) {
  kprint("[");
  bool first = true;
  for (int i = 0; i < v.size(); i++) {
    if (!first)
      kprint(", ");
    first = false;
    kprint(v[i]);
  }
  kprint("]");
}
