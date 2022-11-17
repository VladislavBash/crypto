#include <vector>
#include "Monomial.hpp"
#include "Counter.hpp"
#include "Polynomial.hpp"


    int Polynomial::getSize() const { 
        return this->size;
        }
    Monomial Polynomial::at(int num) const {
        return this->elem[num];
    }
    bool operator== (const Polynomial& a, const Polynomial& b) {
    if (a.getSize() != b.getSize())
        return false;
    int y = 0;
    for (int i =0; i< a.getSize(); i++) {
        if (a.at(i) == b.at(i))
            y++;
    }
    if (y == a.getSize())
        return true;
    return false;
}
// Polynomial operator* (Polynomial a, Polynomial b) {
//     Monomial* arr = new Monomial[std::static_cast<unsigned long long>(a.getSize()*b.getSize())]; // утечка памяти будет: ФИКСИТЬ!
//     int y = 0;
//     for (int i=0; i<a.getSize(); i++) {
//         for (int j=0; j<b.getSize();j++) {
//             arr[y++] = a.at(i)*b.at(j);
//         }
//     }
//     return Polynomial(arr, a.getSize()*b.getSize());
// }



// Polynomial operator+ (Polynomial a, Polynomial b) {
    // Galois_field::Monomial* arr = new Galois_field::Monomial[a.getSize()*b.getSize()];
    // int y = 0;
    // for (int i=0; i<a.getSize(); i++) {
    //     for (int j=0; j<b.getSize();j++) {
    //         arr[y++] = a.at(i)*b.at(j);
    //     }
    // }
    // return Galois_field::Polynomial(arr, a.getSize()*b.getSize());
// }


// Polynomial operator- (Polynomial a, Polynomial b) {
    // Galois_field::Monomial* arr = new Galois_field::Monomial[a.getSize()*b.getSize()];
    // int y = 0;
    // for (int i=0; i<a.getSize(); i++) {
    //     for (int j=0; j<b.getSize();j++) {
    //         arr[y++] = a.at(i)*b.at(j);
    //     }
    // }
    // return Galois_field::Polynomial(arr, a.getSize()*b.getSize());
// }