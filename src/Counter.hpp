#pragma once
#include <vector>
class ERR {};

class Counter { // pow koefs
  public:
  int p;
  int n;
  int size = n;
//   static int* count[n-1] = {};
  // static int* count;
  std::vector<int> count;
  public:
  Counter(int x, int y = 2): p(y), n(x) {
    for (int i=0; i<x; i++) {
      count.push_back(0);
    }
    }
  ~Counter() { }
  std::vector<int> getCount();
  int getSize();
  int getVal(int i);
  // int* operator++(int);
  // Counter& operator++();
  Counter& operator++() {
    int k = this->size - 1;
    this->count[k]++;
    while (this->count[k] == this->p) {
        this->count[k] = 0;
        k--;
        if (k == -1)
          throw ERR();
        this->count[k]++;
    }
    return *this;
}
};