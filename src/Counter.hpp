#pragma once
#include <vector>
#include <stdexcept>

class Counter { // pow koefs
  private:
  int base;
  int size;
//   static int* count[n-1] = {};
  // static int* count;
  std::vector<int> count;
  public:
  Counter(int x, int y = 2): base(y), size(x) {
    for (int i=0; i<x; i++) {
      count.push_back(0);
    }
    }
  ~Counter() {}
  // std::vector<int> getCount();
  int getSize() const;
  int getBase() const;
  int at(int i) const;
  int maxInc() const;
  // int* operator++(int);
  // Counter& operator++();
  Counter& operator++() {
    int k = this->size - 1;
    this->count[size_t(k)]++;
    while (this->count[size_t(k)] == this->base) {
        this->count[size_t(k)] = 0;
        k--;
        if (k == -1)
          throw std::invalid_argument("list index out of range");
        this->count[size_t(k)]++;
    }
    return *this;
}
Counter& operator+(int x) {
    for (int i =0; i<x; i++) {
        ++(*this);
    }
    return *this;
}
};