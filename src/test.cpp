#include "doctest.h"
#include <string>
#include <clocale>
#include <iostream>
#include <bitset>
#include "Affine_Cipher.hpp"
#include "Counter.hpp"
#include "Galois_field.hpp"
#include "Monomial.hpp"
#include "Polynomial.hpp"
#include "Recurrent_Affine_Cipher.hpp"
#include "Substitution_Cipher.hpp"
#include "Translate.hpp"
#include "analysis.hpp"

// std::locale locale("");
// std::locale::global("");

TEST_CASE("TRANSLATE") {
    // setlocale(LC_ALL, "ru-RUS");
    // setlocale(LC_ALL, "ru_RU.UTF-8");
    // std::locale::global( std::locale("ru_RU.UTF-8") );
    // setlocale(LC_ALL, "ru_RU.UTF-8");
	
	// auto str = setlocale(LC_ALL, NULL);
    // std::cout.imbue( std::locale() );
    // setlocale(LC_ALL, "ru_RU.UTF-8");
    // std::locale::global( std::locale("ru_RU.UTF-8") );
    // std::cout.imbue(std::locale("ru_RU.UTF-8"));
    // std::locale("UTF-8");
    // setlocale(LC_ALL, NULL);
    // REQUIRE(translate("A", "eng") == 0);
    // REQUIRE(translate("W", "eng") == 22);
    // std::locale locale("ru_RU.UTF-8");
    std::string o = "кУКУШКА";
    std::string q = "К";
    REQUIRE(o.at(0) == q.at(0));
    REQUIRE(translate("А", "rus") == 0);
    REQUIRE(translate("Ц", "rus") == 21);
    // setlocale(LC_ALL, "en_US.utf8");
	
	// str = setlocale(LC_ALL, NULL);
    // std::cout.imbue( std::locale() );
    // std::locale("en_US.UTF-8");
    // std::locale::global( std::locale("en_US.UTF-8") );
    // std::locale("UTF-8");
    // std::cout.imbue(std::locale("en_US.UTF-8"));
    o = "kUKUSHKA";
    q = "k";
    REQUIRE(o.at(0) == q.at(0));
    REQUIRE(translate("A", "eng") == 0);
    REQUIRE(translate("V", "eng") == 21);
}

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

TEST_CASE("CHECK_NEW_POLYNOMIAL") {
    int base = 2;
    Monomial* lst = new Monomial[2];
    lst[0].setKoef(-1);
    lst[0].setPow(0);
    lst[1].setKoef(-1);
    lst[1].setPow(1);
    auto a = Polynomial{lst, 2, base};
    REQUIRE(a.at(0).getKoef() == -1);
    REQUIRE(a.at(0).getPow() == 0);
    REQUIRE(a.at(1).getKoef() == -1);
    REQUIRE(a.at(1).getPow() == 1);
    Monomial* lt = new Monomial[2];
    lt[0].setKoef(-1);
    lt[0].setPow(1);
    lt[1].setKoef(-1);
    lt[1].setPow(0);
    auto b = Polynomial{lt, 2, base};
    REQUIRE(b.at(0).getKoef() == -1);
    REQUIRE(b.at(0).getPow() == 0);
    REQUIRE(b.at(1).getKoef() == -1);
    REQUIRE(b.at(1).getPow() == 1);
    auto c = a * b;
    REQUIRE(c.at(0).getKoef() == 1);
    REQUIRE(c.at(0).getPow() == 0);
    REQUIRE(c.at(1).getKoef() == 2);
    REQUIRE(c.at(1).getPow() == 1);
    REQUIRE(c.at(2).getKoef() == 1);
    REQUIRE(c.at(2).getPow() == 2);
}

TEST_CASE("CHECK_POLYNOMIAL") {
    // REQUIRE();
    int base = 8;
    Counter lst(2,2);
    ++lst;
    ++lst;
    ++lst;
    Polynomial a{lst, base};
    Polynomial d{{Monomial(1,0), Monomial(1,1)}, base};
    Polynomial b{{Monomial(0,0), Monomial(0,1), Monomial(1,0), Monomial(1,1)}, base};
    Monomial* lt = new Monomial[4] {Monomial(0,0), Monomial(0,1), Monomial(1,0), Monomial(1,1)};
    Polynomial c{lt, 4, base};
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

    Polynomial a1{{Monomial{5,2}, Monomial{1,1}}, base};
    Polynomial a2{{Monomial{3,3}, Monomial{1,2}}, base};
    Polynomial a3{{Monomial{15,5}, Monomial{8,4}, Monomial{1,3}}, base};
    Polynomial a4{{Monomial{1,1}, Monomial{3,3}, Monomial{6,2}}, base};
    REQUIRE(a1*a2 == a3);
    REQUIRE(a1+a2 == a4);
    a1 = {{Monomial{1,0}, Monomial{1,0}}, base};
    a2 = {{Monomial{1,0}, Monomial{1,0}}, base};
    a3 = {{Monomial{4,0}}, base};
    a4 = {{Monomial{4,0}}, base};
    REQUIRE(a1*a2 == a3);
    REQUIRE(a1+a2 == a4);
}

TEST_CASE("CHECK_NEW_GALOIS_FIELD") {
    int base = 2;
    Galois_field g{base, base+6};
    // REQUIRE(g.atMultiTable(Polynomial{{Monomial{1,8}, Monomial{1,0}}, base}, Polynomial{{Monomial{1,1}},base}) == Polynomial{{Monomial{1,0}},base});
    auto i = g.atSumTable(Polynomial{{Monomial{1,7}, Monomial{1,4}, Monomial{1,3}, Monomial{1,0}},base}, Polynomial{{Monomial{1,7}, Monomial{1,6}, Monomial{1,4}, Monomial{1,2}}, base});
    // auto i = g.atSumTable(Polynomial{{Monomial{1,7}, Monomial{1,6}, Monomial{1,4}, Monomial{1,2}}, base}, Polynomial{{Monomial{1,7}, Monomial{1,4}, Monomial{1,3}, Monomial{1,0}},base});
    // REQUIRE(i == Polynomial{{Monomial{1,6}, Monomial{1,3}, Monomial{1,2}, Monomial{1,0}},base});
    // auto y = g.atMultiTable(Polynomial{{Monomial{1,3}, Monomial{1,1}, Monomial{1,0}}, base}, Polynomial{{Monomial{1,2}, Monomial{1,0}},base});
    // REQUIRE(y == Polynomial{{Monomial{1,5}, Monomial{1,2}, Monomial{1,1}, Monomial{1,0}},base});
    // auto a1 = Polynomial{{Monomial{1,1}}, base};
    // auto a2 = Polynomial{{Monomial{1,2}}, base};
    // REQUIRE(g.atMultiTable(a1, a2) == Polynomial{{Monomial{1,1}, Monomial{2,0}}, base});
}

TEST_CASE("CHECK_GALOIS_FIELD") {
    // REQUIRE();
    int base = 2;
    int a1 = 15;
    int b1 = 9;
    Galois_field a{a1,b1};
    Counter c{a1,b1};
    for (int i =0; i<c.maxInc(); i++) {
        REQUIRE(a.group.at(i) == Polynomial(c, base));
        ++c;
    }
    Galois_field g{2,2};
    Counter s{3,2};
    REQUIRE(g.irrPolynomial == Polynomial{s+7, base});
}

TEST_CASE("CHECK_SUBSTIOTUTION_CIPHER") {
    // REQUIRE();
    // std::map<char, char> key{{'A','B'},{'B','C'},{'C','D'},{'D','A'}};
    // Substitution_Cipher a{key};
    // REQUIRE(a.getKey().at('A') == 'B');
    // REQUIRE(a.getKey().at('B') == 'C');
    // REQUIRE(a.getKey().at('C') == 'D');
    // REQUIRE(a.getKey().at('D') == 'A');
    // REQUIRE(a.getRkey().at('A') == 'D');
    // REQUIRE(a.getRkey().at('B') == 'A');
    // REQUIRE(a.getRkey().at('C') == 'B');
    // REQUIRE(a.getRkey().at('D') == 'C');
    // a.setOpText(std::string("dCab"));
    // REQUIRE(a.Encrypt() == std::string("ADBC"));
    // REQUIRE(a.Decrypt() == std::string("DCAB"));
    std::string text = "dCaD";
    // std::string k = "bcda";
    std::string k = "GUOPDXEKHFMYWCNRTBSQJIAVZL";
    Substitution_Cipher b{k};
    b.setOpText(text);
    // REQUIRE(b.Encrypt() == std::string("ADBC"));
    // REQUIRE(b.Decrypt() == std::string("DCAB"));
    REQUIRE(b.Encrypt() == std::string("POGP"));
    REQUIRE(b.Decrypt() == std::string("DCAD"));
}

TEST_CASE("CHECK_AFFINE_CIPHER") {
    // REQUIRE();
    // std::string optext = "AABCDC"; 
    // std::string optext = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string optext = "ABCDEFGHIJKLMNOPQRSTUVWXYZYXWVUTSRQPONMLKJIHGFEDCBA";
    // std::string optext = "Q";
    int a = 3;
    int b = 2;
    std::string cltext = Affine_Cipher::Encrypt(optext, a, b, "eng", 4); // РАБОТАЕТ!!!!!
    std::string test = Affine_Cipher::Decrypt(cltext, a, b, "eng", 4);
    REQUIRE(optext == test);
}

TEST_CASE("CHECK_RECCURENT_AFFINE_CIPHER") {
    // REQUIRE();
    // std::string optext = "AABCDC";
    // std::string optext = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string optext = "ABCDEFGHIJKLMNOPQRSTUVWXYZZYXWVUTSRQPONMLKJIHGFEDCBA";
    int a1 = 2;
    int a2 = 3;
    int b1 = 4;
    int b2 = 6;
    std::string cltext = Recurrent_Affine_Cipher::Encrypt(optext, a1, a2, b1, b2, "eng", 4); // РАБОТАЕТ!!!!!
    std::string test = Recurrent_Affine_Cipher::Decrypt(cltext, a1, a2, b1, b2, "eng", 4);
    REQUIRE(optext == test);
}

std::string TextToBinaryString(std::string words) {
    std::string binaryString = "";
    for (const char& _char : words) {
        binaryString +=std::bitset<8>(_char).to_string();
    }
    return binaryString;
}

TEST_CASE("STR_AS_BITSET") {
    std::string optext = "HELLO";
    REQUIRE(TextToBinaryString(optext) == "0100100001000101010011000100110001001111");
    REQUIRE(TextToBinaryString(optext.substr(0,1)) == "01001000");
    REQUIRE(TextToBinaryString(optext.substr(1,1)) == "01000101");
    REQUIRE(TextToBinaryString(optext.substr(2,1)) == "01001100");
    REQUIRE(TextToBinaryString(optext.substr(3,1)) == "01001100");
    REQUIRE(TextToBinaryString(optext.substr(4,1)) == "01001111");
}

// TEST_CASE("STR_AS_BITSET") {
//     std::string optext = "HELLO";
//     std::string binoptext = TextToBinaryString(optext);
//     SUBCASE("STR_AS_BITSET") {
//         REQUIRE(binoptext == "0100100001000101010011000100110001001111");
//         REQUIRE(TextToBinaryString(optext.substr(0,1)) == "01001000");
//         REQUIRE(TextToBinaryString(optext.substr(1,1)) == "01000101");
//         REQUIRE(TextToBinaryString(optext.substr(2,1)) == "01001100");
//         REQUIRE(TextToBinaryString(optext.substr(3,1)) == "01001100");
//         REQUIRE(TextToBinaryString(optext.substr(4,1)) == "01001111");
//     }
//     SUBCASE("AFFINE_CIPHER") {
//         int a = 9;
//         int b = 25;
//         std::string cltext = Affine_Cipher::Encrypt(binoptext, a, b, "eng"); // РАБОТАЕТ!!!!!
//         std::string test = Affine_Cipher::Decrypt(cltext, a, b, "eng");
//         REQUIRE(optext == test);
//     }
//     SUBCASE("RECCURENT_AFFINE_CIPHER") {
//         int a1 = 2;
//         int a2 = 3;
//         int b1 = 4;
//         int b2 = 6;
//         std::string cltext = Recurrent_Affine_Cipher::Encrypt(binoptext, a1, a2, b1, b2, "eng"); // РАБОТАЕТ!!!!!
//         std::string test = Recurrent_Affine_Cipher::Decrypt(cltext, a1, a2, b1, b2, "eng");
//         REQUIRE(optext == test);
//     }
// }
TEST_CASE("ANALYSIS") {
    std::string clText = "";
    std::string word = "HELLO";
    std::string opText = "HELLOABCDEFGHIJKLMNOPQRSTUVWXYZZYXWVUTSRQPONMLKJIHGFEDCBA"; // 7 pos
    int a1 = 2;
    int a2 = 3;
    int b1 = 4;
    int b2 = 6;
    clText = Recurrent_Affine_Cipher::Encrypt(opText, a1, a2, b1, b2, "eng");
    REQUIRE(analysis(clText, word) == opText);
}