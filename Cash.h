#include "Card.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

class Cash {
public:
    std::vector<int> iloscBanknotow;
    std::vector<int> iloscBanknotowTemp;
    std::vector<int> nominalyBanknotow;
    std::vector<int> nominalyBanknotowTemp;
    std::vector<int> pustyWektorInt;

    void wczytajDaneZPliku(const std::string& nazwaPliku);
    void wypiszIlosciNominalow() const;
    std::vector<int> algorytm_zachlanny(int kwota);
    void zapiszDoPliku(const std::string& nazwaPliku) const;
    void kwota_do_wydania(int kwota);
    void wyczyscDane();
    bool isMouseOverOnCashhole(RenderWindow& window, float x, float y, float xx, float yy);
};

