#include "Card.h"
#include "Cash.h"
#include "Atm.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

extern Cash cash;
extern Atm bankomat;
extern Text writing;
bool wydajemy = false;

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
    std::string napis;
    for (size_t i = 0; i < iloscBanknotow.size(); ++i) {
        std::cout << "Nominal: " << nominalyBanknotow[i] << " PLN, Ilosc sztuk: " << iloscBanknotow[i] << std::endl;
    }
    
    
}

//std::vector<int> iteracja(int kwota, std::vector<int> &wektor, std::vector<int> &nominaly) {
//    for (int i = 0; i < wektor.size(); ) {
//
//    }
//    
//}

std::vector<int> Cash::algorytm_zachlanny(int kwota) {
    std::vector<int> wydaneBanknoty(iloscBanknotow.size(), 0); // Inicjalizacja wektora z iloœciami wydanych banknotów
    std::vector<int> wydaneBanknotyTemp(iloscBanknotow.size(), 0);
    std::vector<int> suma_w_banknotach(iloscBanknotow.size(), 0);
    std::vector<int> suma_w_banknotachTemp(iloscBanknotow.size(), 0);
    int suma = 0;
    wydajemy = false;
    //int indeks;

    for (int i = 0; i < iloscBanknotow.size(); i++) {
        suma_w_banknotach[i] = nominalyBanknotow[i] * iloscBanknotow[i];
        suma += nominalyBanknotow[i] * iloscBanknotow[i];
        //std::cout << suma << std::endl;
    }
    suma_w_banknotachTemp = suma_w_banknotach;
    if (kwota > suma) {
        std::cout << "Nie mozna wydac kwoty " << kwota << ". Brak srodkow w bankomacie." << std::endl;
        wydajemy = false;
        return pustyWektorInt;
        //return wydaneBanknoty; // Zwracamy pusty wektor, bo nie mo¿na wydaæ ¿adnych banknotów
    }

    int kwota_temp = kwota;
    wydaneBanknotyTemp = wydaneBanknoty;
    iloscBanknotowTemp = iloscBanknotow;
    for (int i = 0; i < iloscBanknotow.size(); i++) {
        
        while (kwota >= nominalyBanknotow[i] and iloscBanknotow[i] > 0) {
            kwota -= nominalyBanknotow[i];
            wydaneBanknoty[i]++;
            iloscBanknotow[i]--;
        }
    }
    if (kwota == 0) {
        wydajemy = true;
    }
    else if (kwota > 0) {
        wydajemy = false;
        std::cout << "Nie mozna dokladnie wydac kwoty " << kwota << " pierwszym algorytmem. " << std::endl;
        std::cout << "Sprawdzmy drugim algorytmem" << std::endl;
        kwota = kwota_temp;
        wydaneBanknoty = wydaneBanknotyTemp;
        iloscBanknotow = iloscBanknotowTemp;

        for (int i = 0; i < iloscBanknotow.size(); i++) {
            while (kwota <= suma_w_banknotach[i] and kwota >= nominalyBanknotow[i] and iloscBanknotow[i] > 0 or kwota >= nominalyBanknotow[i] and iloscBanknotow[i] > 0) {
                    std::cout << "Odejmujemy od: " << kwota << "nominal: " << nominalyBanknotow[i] << "\n";
                    kwota -= nominalyBanknotow[i];
                    suma_w_banknotach[i] -= nominalyBanknotow[i];
                    wydaneBanknoty[i]++;
                    iloscBanknotow[i]--;
                    if (kwota == 0) {
                        wydajemy = true;
                        break;
                    }
            }
            if (kwota == 0) {
                wydajemy = true;
                break;
            }
            else if (nominalyBanknotow[i] != 10 and kwota <= nominalyBanknotow[i + 1] and kwota <= suma_w_banknotach[i + 1] and iloscBanknotow[i] < iloscBanknotowTemp[i]) {
                std::cout << "Dodajemy do: " << kwota << "odjety wczesniej nominal: " << nominalyBanknotow[i] << "\n";
                kwota += nominalyBanknotow[i];
                suma_w_banknotach[i] += nominalyBanknotow[i];
                wydaneBanknoty[i]--;
                iloscBanknotow[i]++;
            }
        }
    }
    if (wydajemy == false) {
        kwota = kwota_temp;
        std::cout << "Kwota dla 3 proby: " << kwota << "\n";
        wydaneBanknoty = wydaneBanknotyTemp;
        iloscBanknotow = iloscBanknotowTemp;
        int kwotaWydania = 0;

        for (int n = iloscBanknotow.size() - 1; n >= 0; n--) {
            if (kwota == 0)
            {
                wydajemy = true;
                break;
            }
            while (kwota % nominalyBanknotow[n] == 0 and suma_w_banknotach[n] >= kwota)
            {
                kwota -= nominalyBanknotow[n];
                suma_w_banknotach[n] -= nominalyBanknotow[n];
                wydaneBanknoty[n]++;
                iloscBanknotow[n]--;
                if (kwota == 0)
                {
                    wydajemy = true;
                    break;
                }
            }
        }
    }

    if(wydajemy == true){
        zapiszDoPliku("banknoty.txt");
        std::cout << "Stan banknotow po wyplacie zaktualizowany." << std::endl;
        screen_event = screen_e::odbierz_karte;
    } else {
        std::cout << "Nie mozna dokladnie wydac kwoty " << kwota << ". Brak odpowiednich banknotow." << std::endl;
        return pustyWektorInt;
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

void Cash::drawCash(RenderWindow& window) {

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

    if (wydajemy == true) {
        std::cout << "Wydane banknoty dla kwoty " << kwotaDoWydania << " to:" << std::endl;
        for (size_t i = 0; i < wydaneBanknoty.size(); ++i) {
            if (wydaneBanknoty[i] > 0) {
                std::cout << wydaneBanknoty[i] << " banknotow o nominale " << nominalyBanknotow[i] << std::endl;
            }
        }
        std::cout << "Stan banknotow po wyplacie:\n" << std::endl;
        wypiszIlosciNominalow();
    } else {
        std::cout << "Stan banknotow po NIEUDANEJ wyplacie:\n" << std::endl;
        wypiszIlosciNominalow();
    }
    wyczyscDane();
}

bool Cash::isMouseOverOnCashhole(RenderWindow& window, float x, float y, float xx, float yy) {
    int mouseX = Mouse::getPosition(window).x;
    int mouseY = Mouse::getPosition(window).y;

    float btnPosX = x;
    float btnPosY = y;

    float btnxPosWidth = xx;
    float btnyPosHeight = yy;

    if (mouseX < btnxPosWidth and mouseX > btnPosX and mouseY < btnyPosHeight and mouseY > btnPosY) {
        return true;
    }
    return false;
}