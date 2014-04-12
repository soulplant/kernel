#ifndef VECTOR_H_
#define VECTOR_H_

#include <stddef.h>

#include "kprint.h"

namespace {

template<class T>
T&& move(T&& t) {
  return static_cast<T&&>(t);
}

}

template<class T>
class Vector {
 public:
  Vector()
      : items_(nullptr),
        size_(0),
        capacity_(0) {
    kprintln("Vector::Vector()");
  }

  Vector(const Vector& other) = delete;

  ~Vector() {
    kprintln("Vector::~Vector()");
    delete[] items_;
  }

  void push_back(const T& t) {
    ensure_capacity(size_ + 1);
    items_[size_] = t;
    size_++;
  }

  void emplace_back(T&& t) {
    ensure_capacity(size_ + 1);
    items_[size_] = move(t);
    size_++;
  }

  void erase(int i) {
    for (int j = i; j < size_ - 1; j++)
      items_[j] = items_[j + 1];
    items_[size_ - 1] = T();
    size_--;
  }

  T& operator [](size_t i) const {
    return items_[i];
  }

  size_t size() const { return size_; }

 private:
  void ensure_capacity(size_t target) {
    if (capacity_ >= target)
      return;

    if (target < capacity_ * 2)
      target = capacity_ * 2;

    T* new_items = new T[target];
    for (int i = 0; i < size_; i++)
      new_items[i] = items_[i];
    delete[] items_;
    items_ = new_items;
    capacity_ = target;
  }

  T* items_;
  size_t size_;
  size_t capacity_;
};

#endif  // VECTOR_H_
