#include "Counter.h"


int Counter::getSize() { return this->size; }
int Counter::getVal(int i) { return this->count[i]; }
// Counter& Counter::operator++() {
//     int k = this->size - 1;
//     this->count[k]++;
//     while (this->count[k] == this->p) {
//         this->count[k] = 0;
//         k--;
//         this->count[k]++;
//     }
//     return *this;
// }
// int* Counter::operator++(int) {
//     int k = this->size - 1;
//     this->count[k]++;
//     while (this->count[k] == p) {
//         this->count[k] = 0;
//         k--;
//         this->count[k]++;
//     }
//     return this->count;
// }

// int*& Counter::operator++() {
//     int k = this->size - 1;
//     this->count[k]++;
//     while (this->count[k] == p) {
//         this->count[k] = 0;
//         k--;
//         this->count[k]++;
//     }
//     return this->count;
// }