#include <vector>
#include <map>
#include "Galois_field.hpp"
#include "Polynomial.hpp"


// int times(int x, int y) {
//     int s = 0;
//     for (int z=0; z<y-1; z++) {
//         s += pow(x, z);
//     }
//     return (x-1)*s;
// }
int rem(int x, int r) {
    while (x < 0) {
        x += r;
    }
    return x;
}

Polynomial fun(Polynomial c, int base) {
    int s = c.getSize();
    for (int i =0; i<c.getSize(); i++) {
        auto q = c.at(i);
        auto r = rem(q.getKoef(), base);
        if (r == 0)
            s--;
        q.setKoef(r);
    }
    Monomial* lst = new Monomial[size_t(s)];
    int j = 0;
    for (int i=0; i<s; i++) {
        if (c.at(i).getKoef() == 0) {
        } else {
            lst[j].setKoef(c.at(i).getKoef());
            lst[j].setPow(c.at(i).getPow());
            j++;
        }
    }
    return Polynomial{lst, s};
}

Galois_field::Galois_field(int y, int x = 2): base(x), pow(y) { // base pow
    constructPole();
    constructGroup();
    constructIrrPolynomial();
    constructMultiGroup();
    constructSumTable();
    constructMultiTable();
}

void Galois_field::constructPole() {
    for (int i=0; i<this->base; i++) {
        this->pole.push_back(i);
    }
}

void Galois_field::constructGroup() {
    Counter c{this->pow,this->base};
    for (int k=0; k<c.maxInc(); k++) {
        this->group.push_back(Polynomial{c}); // 000 y = 3   0000 y = 4
        ++c;
    }
    this->group.push_back(Polynomial{c});
}

void Galois_field::constructIrrPolynomial() {
    Counter c{this->pow, this->base};
    Counter d{this->pow+1, this->base};
    d = d + c.maxInc() ;
    int cont = 0;
    for (int i=0; i<=c.maxInc(); i++) {
        ++d;
        auto y = Polynomial{d};
        for (auto x: this->pole) {
            auto cac = y.calc(x, this->base);
            if (y.calc(x, this->base) != 0)
                cont++;
        }
        if (cont == this->base) {
            this->irrPolynomial = y;
            break;
        }
        cont = 0;
    }
}

void Galois_field::constructMultiGroup() {
    this->multiGroup = this->group;
    this->multiGroup.erase(this->multiGroup.begin());
}

void Galois_field::constructSumTable() {
    std::vector<Polynomial> v;
    int cont1 = 0;
    int cont2 = 0;
    for (auto j: this->group) {
        // sumTable.push_back();
        // auto y = std::map<Polynomial, Polynomial> {j,j};
        // sumTable.insert({j, y});
        // sumTable.insert({j, std::map<Polynomial,Polynomial>()});
        // sumTable[j].insert(std::make_pair(j,j));
        // sumTable.insert(std::make_pair(j,std::map<Polynomial, Polynomial>(j,j)));
        for (auto i: this->group) {
            if (cont1 < cont2) {
                v.push_back(sumTable.at(i.getVal()).at(j.getVal()));
                cont1++;
            } else {
                v.push_back(sum(j, i));
            }
            // sumTable[j] = {i, i};
            // sumTable[j].insert(std::make_pair(i,i));
            // auto elem = sum(j, i);
            // inSumTable(j, i, elem);
        }
        sumTable.push_back(v);
        v.clear();
        cont2++;
    }
}

void Galois_field::constructMultiTable() {
    // for (auto j: this->group) {
    //     for (auto i: this->group) {
    //         auto elem = multi(j, i);
    //         if (elem == Polynomial{Monomial{1,0}})
    //             this->revVector.insert({i,j});
    //         inMultiTable(j, i, elem);
    //     }
    // }
    std::vector<Polynomial> v;
    int cont1 = 0;
    int cont2 = 0;
    for (auto j: this->multiGroup) {
        // sumTable.push_back();
        // auto y = std::map<Polynomial, Polynomial> {j,j};
        // sumTable.insert({j, y});
        // sumTable.insert({j, std::map<Polynomial,Polynomial>()});
        // sumTable[j].insert(std::make_pair(j,j));
        // sumTable.insert(std::make_pair(j,std::map<Polynomial, Polynomial>(j,j)));
        for (auto i: this->multiGroup) {
            if (cont1 < cont2) {
                v.push_back(multiTable.at(i.getVal()-1).at(j.getVal()-1));
                cont1++;
            } else {
                auto y = multi(j, i);
                v.push_back(y);
                if (y == Polynomial{Monomial{1,0}})
                    this->revVector.push_back(y);
            }
            // sumTable[j] = {i, i};
            // sumTable[j].insert(std::make_pair(i,i));
            // auto elem = sum(j, i);
            // inSumTable(j, i, elem);
        }
        multiTable.push_back(v);
        v.clear();
        cont2++;
    }
}

// void Galois_field::constructRevVector() {

// }

Polynomial Galois_field::atSumTable(Polynomial first, Polynomial second) {
    // auto &a = this->sumTable.at(first);
    // return a.at(second);
    return sumTable.at(first.getVal()).at(second.getVal());
}

Polynomial Galois_field::atMultiTable(Polynomial first, Polynomial second) {
    // auto &a = this->multiTable.at(first);
    // return a.at(second);
    return multiTable.at(first.getVal()).at(second.getVal());
}

// void Galois_field::inSumTable(Polynomial first, Polynomial second, Polynomial elem) {
//     // auto &a = this->sumTable.at(first);
//     // a.insert({second, elem});

//     // this->sumTable[first][second] = elem;
// }

// void Galois_field::inMultiTable(Polynomial first, Polynomial second, Polynomial elem) {
//     // auto &a = this->multiTable.at(first);
//     // a.insert({second, elem});

//     // this->multiTable[first][second] = elem;
// }

Polynomial Galois_field::sum(Polynomial a, Polynomial b) {
    Polynomial c = a + b;
    // int s = c.getSize();
    // for (int i =0; i<c.getSize(); i++) {
    //     auto q = c.at(i);
    //     auto r = rem(q.getKoef(), this->base);
    //     if (r == 0)
    //         s--;
    //     q.setKoef(r);
    // }
    // Monomial* lst = new Monomial[size_t(s)];
    // int j = 0;
    // for (int i=0; i<s; i++) {
    //     if (c.at(i).getKoef() == 0) {
    //     } else {
    //         lst[j].setKoef(c.at(i).getKoef());
    //         lst[j].setPow(c.at(i).getPow());
    //         j++;
    //     }
    // }
    // return Polynomial{lst, s};
    return fun(c, this->base);
}

Polynomial Galois_field::multi(Polynomial a, Polynomial b) {
    Polynomial c = a * b;
    return fun(c, this->base);
}
// Galois_field::Galois_field(int y, int x = 2) {
//     for (int i=0; i<x; i++) {
//         this->pole.push_back(i);
//     }
//     Counter c{y,x};
//     for (int k=0; k<times(x,y); k++) {
//         this->group.push_back(Polynomial{c}); // 000 y = 3   0000 y = 4
//         ++c;
//     }
// }