#include "doctest.h"
#include <string>
#include "Affine_Cipher.hpp"
#include "Counter.hpp"
#include "Galois_field.hpp"
#include "Monomial.hpp"
#include "Polynomial.hpp"
#include "Recurrent_Affine_Cipher.hpp"
#include "Substitution_Cipher.hpp"


TEST_CASE("CHECK_COUNTER") {
    // Counter a(5,3); //0000
    // // int* lst = new int[4]{0,0,0,1};
    // // REQUIRE(a.count[0] == 0); // 0001
    // // REQUIRE(a.count[1] == 0); // 0001
    // // REQUIRE(a.count[2] == 0); // 0001
    // // //a++;
    // // REQUIRE((++a).count[3] == 1); // 0001
    // // // ++a;
    // // REQUIRE((++a).count[3] == 0); // 0001
    // // REQUIRE(a.count[2] == 1); // 0001


    // REQUIRE(a.count[5-2] == 0);
    // REQUIRE((++a).count[5-2] == 1);
    // REQUIRE((++a).count[5-2] == 2);
    // REQUIRE((++a).count[5-3] == 1);
    // REQUIRE(a.count[5-2] == 0);


    Counter a(2,2); // 0 1
    // int* lst = new int[4]{0,0,0,1};
    // REQUIRE(a.count[0] == 0); // 0001
    // REQUIRE(a.count[1] == 0); // 0001
    // REQUIRE(a.count[2] == 0); // 0001
    // //a++;
    // REQUIRE((++a).count[3] == 1); // 0001
    // // ++a;
    // REQUIRE((++a).count[3] == 0); // 0001
    // REQUIRE(a.count[2] == 1); // 0001


    REQUIRE(a.at(1) == 0);
    REQUIRE(a.at(0) == 0);
    ++a;
    REQUIRE(a.at(1) == 1);
    REQUIRE(a.at(0) == 0);
    ++a;
    REQUIRE(a.at(1) == 0);
    REQUIRE(a.at(0) == 1);
    ++a;
    REQUIRE(a.at(1) == 1);
    REQUIRE(a.at(0) == 1);

    Counter c(3,2);
    int u = c.maxInc();
    for (int j=0; j<c.maxInc(); j++) {
        for (int i =0; i<a.getSize(); i++) {
            int l = j / pow(c.getBase(),i);
            int o = c.at(c.getSize()-1-i);
            REQUIRE(c.at(c.getSize()-1-i) == (l % c.getBase()));
        }
        ++c;
    }

    Counter d{5,6};
    auto i = d.maxInc();
    d = d + 7425;
    REQUIRE(d.at(0) == 5);
    REQUIRE(d.at(1) == 4);
    REQUIRE(d.at(2) == 2);
    REQUIRE(d.at(3) == 1);
    REQUIRE(d.at(4) == 3);
    // REQUIRE(a.count[5-2] == 0);
    // REQUIRE((++a).count[5-2] == 1);
    // REQUIRE((++a).count[5-3] == 1);
    // REQUIRE(a.count[5-2] == 0);
    // REQUIRE((++a).count[5-3] == 1);
    // REQUIRE(a.count[5-2] == 1);
    // REQUIRE((++a).count[5-4] == 1);


    // for (int i = 5-2; i>=0; i--) {
    //     REQUIRE((++a).count[i] == 1);
    // }

    // REQUIRE(getRatio(2) == 31.599);
    // REQUIRE(getRatio(11) == 4.436);
    // REQUIRE(getRatio(22) == 3.792);
    // REQUIRE(getRatio(30) == 3.645);
    // REQUIRE(getRatio(60) == 3.460);
    // REQUIRE(getRatio(120) == 3.373);
    // REQUIRE(getRatio(12000000) == 3.373);
    // REQUIRE(getRatio(1147483646) == 3.290);
}

TEST_CASE("CHECK_MONOMIAL") {
    // int k = 12;
    // int p = 14;
    // Monomial a{k, p};
    // REQUIRE(a.getKoef() == k);
    // REQUIRE(a.getPow() == p);
    // std::string str = "*x^";
    // str = std::to_string(k) + str + std::to_string(p);
    // Monomial b{str};
    // REQUIRE(b.getKoef() == k);
    // REQUIRE(b.getPow() == p);
    // REQUIRE(a == b);
    int k = 12;
    int p = 32;
    Monomial a{k, p};
    Monomial b{k, p};
    REQUIRE(a == b);
    REQUIRE(a*b == Monomial{k*k, p+p});
}

TEST_CASE("CHECK_POLYNOMIAL") {
    // REQUIRE();
    Counter lst(2,2);
    ++lst;
    ++lst;
    ++lst;
    Polynomial a{lst};
    Polynomial d{Monomial(1,0), Monomial(1,1)};
    Polynomial b{Monomial(0,0), Monomial(0,1), Monomial(1,0), Monomial(1,1)};
    Monomial* lt = new Monomial[4] {Monomial(0,0), Monomial(0,1), Monomial(1,0), Monomial(1,1)};
    Polynomial c{lt,4};
    // delete lt;
    REQUIRE(a == d);
    REQUIRE(b.at(0).getKoef() == 0);
    REQUIRE(b.at(0).getPow() == 0);
    REQUIRE(b.at(1).getKoef() == 0);
    REQUIRE(b.at(1).getPow() == 1);
    REQUIRE(b.at(2).getKoef() == 1);
    REQUIRE(b.at(2).getPow() == 0);
    REQUIRE(b.at(3).getKoef() == 1);
    REQUIRE(b.at(3).getPow() == 1);
    REQUIRE(c.at(0).getKoef() == 0);
    REQUIRE(c.at(0).getPow() == 0);
    REQUIRE(c.at(1).getKoef() == 0);
    REQUIRE(c.at(1).getPow() == 1);
    REQUIRE(c.at(2).getKoef() == 1);
    REQUIRE(c.at(2).getPow() == 0);
    REQUIRE(c.at(3).getKoef() == 1);
    REQUIRE(c.at(3).getPow() == 1);
    REQUIRE(b == c);

    Polynomial a1{Monomial{5,2}, Monomial{1,1}};
    Polynomial a2{Monomial{3,3}, Monomial{1,2}};
    Polynomial a3{Monomial{15,5}, Monomial{8,4}, Monomial{1,3}};
    Polynomial a4{Monomial{1,1}, Monomial{3,3}, Monomial{6,2}};
    REQUIRE(a1*a2 == a3);
    REQUIRE(a1+a2 == a4);
    a1 = {Monomial{1,0}, Monomial{1,0}};
    a2 = {Monomial{1,0}, Monomial{1,0}};
    a3 = {Monomial{4,0}};
    a4 = {Monomial{4,0}};
    REQUIRE(a1*a2 == a3);
    REQUIRE(a1+a2 == a4);
}

TEST_CASE("CHECK_GALOIS_FIELD") {
    // REQUIRE();
    Galois_field a{2,2};
    Counter c{2,2};
    ++c;
    ++c;
    REQUIRE(a.group.at(2) == Polynomial(c));
}

TEST_CASE("CHECK_SUBSTIOTUTION_CIPHER") {
    // REQUIRE();
    std::map<char, char> key{{'A','B'},{'B','C'},{'C','D'},{'D','A'}};
    Substitution_Cipher a{key};
    REQUIRE(a.getKey().at('A') == 'B');
    REQUIRE(a.getKey().at('B') == 'C');
    REQUIRE(a.getKey().at('C') == 'D');
    REQUIRE(a.getKey().at('D') == 'A');
    REQUIRE(a.getRkey().at('A') == 'D');
    REQUIRE(a.getRkey().at('B') == 'A');
    REQUIRE(a.getRkey().at('C') == 'B');
    REQUIRE(a.getRkey().at('D') == 'C');
    a.setOpText(std::string("dCab"));
    REQUIRE(a.Encrypt() == std::string("ADBC"));
    REQUIRE(a.Decrypt() == std::string("DCAB"));
}

TEST_CASE("CHECK_AFFINE_CIPHER") {
    // REQUIRE();
}

TEST_CASE("CHECK_RECCURENT_AFFINE_CIPHER") {
    // REQUIRE();
}
