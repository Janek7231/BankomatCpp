#include "Card.h"
#include "Cash.h"
#include "Atm.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

extern Cash cash;
//extern int screen_event;

void Cash::wczytajDaneZPliku(const std::string& nazwaPliku) {
    std::ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        std::cout << "Nie udalo sie otworzyc pliku: " << nazwaPliku << std::endl;
        return;
    }

    int ilosc, nominal;
    while (plik >> ilosc >> nominal) {
        iloscBanknotow.push_back(ilosc);
        nominalyBanknotow.push_back(nominal);
    }

    plik.close();
}

void Cash::wypiszIlosciNominalow() const {
    for (size_t i = 0; i < iloscBanknotow.size(); ++i) {
        std::cout << "Nominal: " << nominalyBanknotow[i] << "zl, Ilosc sztuk: " << iloscBanknotow[i] << std::endl;
    }
}

std::vector<int> Cash::algorytm_zachlanny(int kwota) {
    std::vector<int> wydaneBanknoty(iloscBanknotow.size(), 0); // Inicjalizacja wektora z iloœciami wydanych banknotów

    int suma = 0;
    for (int i = 0; i < iloscBanknotow.size(); i++) {
        suma += nominalyBanknotow[i] * iloscBanknotow[i];
        std::cout << suma << std::endl;
    }

    if (kwota > suma) {
        std::cout << "Nie mozna wydac kwoty " << kwota << ". Brak odpowiednich banknotow." << std::endl;
        return wydaneBanknoty; // Zwracamy pusty wektor, bo nie mo¿na wydaæ ¿adnych banknotów
    }

    for (int i = 0; i < iloscBanknotow.size(); i++) {
        while (kwota >= nominalyBanknotow[i] && iloscBanknotow[i] > 0) {
            kwota -= nominalyBanknotow[i];
            wydaneBanknoty[i]++;
            iloscBanknotow[i]--;
        }
    }

    if (kwota > 0) {
        std::cout << "Nie mozna dokladnie wydac kwoty " << kwota << ". Brak odpowiednich banknotow." << std::endl;
        // Zwracamy czêœciowy wynik, ale mo¿emy te¿ zwróciæ pusty wektor lub podj¹æ inne decyzje zale¿nie od wymagañ
        //return wydaneBanknoty; // Zwracamy pusty wektor, bo nie mo¿na wydaæ ¿adnych banknotów
    } else {
        zapiszDoPliku("banknoty.txt");
        std::cout << "Stan banknotow po wyplacie zaktualizowany." << std::endl;
        screen_event = screen_e::odbierz_karte;
    }

    return wydaneBanknoty;
}

void Cash::zapiszDoPliku(const std::string& nazwaPliku) const {
    std::ofstream plik(nazwaPliku);
    if (!plik.is_open()) {
        std::cerr << "Nie udalo sie otworzyc pliku: " << nazwaPliku << " do zapisu." << std::endl;
        return;
    }

    for (size_t i = 0; i < iloscBanknotow.size(); ++i) {
        plik << iloscBanknotow[i] << " " << nominalyBanknotow[i] << std::endl;
    }

    plik.close();
}

void Cash::wyczyscDane() {
    iloscBanknotow.clear();
    nominalyBanknotow.clear();
}

void Cash::kwota_do_wydania(int kwota) {
    wczytajDaneZPliku("banknoty.txt");
    std::cout << "\nStan banknotow przed wyplata:" << std::endl;
    wypiszIlosciNominalow();

    int kwotaDoWydania = kwota;
    std::vector<int> wydaneBanknoty = algorytm_zachlanny(kwotaDoWydania);

    std::cout << "Wydane banknoty dla kwoty " << kwotaDoWydania << " to:" << std::endl;
    for (size_t i = 0; i < wydaneBanknoty.size(); ++i) {
        if (wydaneBanknoty[i] > 0) {
            std::cout << wydaneBanknoty[i] << " banknotow o nominale " << nominalyBanknotow[i] << std::endl;
        }
    }

    std::cout << "Stan banknotow po wyplacie:\n" << std::endl;
    wypiszIlosciNominalow();
    wyczyscDane();
}

bool Cash::isMouseOverOnCashhole(RenderWindow& window, float x, float y, float xx, float yy) {
    int mouseX = Mouse::getPosition(window).x;
    int mouseY = Mouse::getPosition(window).y;

    float btnPosX = x;
    float btnPosY = y;

    float btnxPosWidth = xx;
    float btnyPosHeight = yy;

    if (mouseX < btnxPosWidth and mouseX > btnPosX && mouseY < btnyPosHeight and mouseY > btnPosY) {
        return true;
    }
    return false;
}