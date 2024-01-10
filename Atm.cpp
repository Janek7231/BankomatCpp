#include "Atm.h"
#include "Button.h"
#include "Card.h"
#include "Cash.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>

extern Card* uzywana;
extern Cash cash;
extern int helper;
extern bool cash_in;
extern bool card_in;


Atm::Atm(RenderWindow& window_d, float width, float height) 
{
	if (!font.loadFromFile("Anonymous_Pro.ttf"))
	{
		std::cout << "Nie znaleziono czcionki" << std::endl;
	}
	//float width = window.getSize().x;
	//float height = window.getSize().y;
	word[0].setFont(font);
	word[0].setFillColor(Color::White);
	word[0].setString("Informacje o karcie:");
	word[0].setCharacterSize(30);
	word[0].setPosition(width - 550, 20);

	setInfo("","","");

	word[1].setFont(font);
	word[1].setFillColor(Color::White);
	word[1].setCharacterSize(20);
	word[1].setPosition(width - 700, 80);

	word[2].setFont(font);
	word[2].setFillColor(Color::White);
	word[2].setCharacterSize(20);
	word[2].setPosition(width - 700, 110);
		 
	word[3].setFont(font);
	word[3].setFillColor(Color::White);
	word[3].setCharacterSize(20);
	word[3].setPosition(width - 700, 140);
	
	for (int i = 0; i < Writings; i++) {
		writing[i].setFont(font);
		writing[i].setCharacterSize(20);
		writing[i].setFillColor(Color::White);
	}
	
	writing[0].setString("WLOZ KARTE");
	writing[0].setPosition(280 , 150);
;
	writing[1].setString("WPROWADZ PIN:\n    ");
	writing[1].setPosition(250, 250);

	//writing[2].setString("<<WPLATA");
	//writing[2].setPosition(left3);

	writing[3].setString("<<WYPLATA");
	writing[3].setPosition(left4);

	writing[4].setString("ZMIANA PIN>>");
	writing[4].setPosition(55+right3);

	writing[5].setString("DOSTEPNE SRODKI>>");
	writing[5].setPosition(right4);

	writing[6].setString("AKCEPTUJ>>");
	writing[6].setPosition(55 + right2);

	writing[7].setString("POPRAW>>");
	writing[7].setPosition(55 + right3);

	writing[8].setString("ANULUJ>>");
	writing[8].setPosition(55 + right4);

	writing[9].setString("DOSTEPNE SRODKI: ");
	writing[9].setPosition(250, 250);

	writing[10].setString("ZAKONCZ>>");
	writing[10].setPosition(55 + right2);

	writing[11].setString("NIEPOPRAWNY PIN\nWPROWADZ PIN PONOWNIE:\n    ");
	writing[11].setPosition(200, 250);

	writing[12].setString("PODAJ KWOTE: \n    ");
	writing[12].setPosition(200, 250);

	writing[13].setString("WPROWADZ PIN PONOWNIE:\n    ");
	writing[13].setPosition(200, 250);

	writing[14].setString("WYBIERZ KWOTE\n  WYPLATY:\n    ");
	writing[14].setPosition(270, 150);

	writing[15].setString("50\n");
	writing[15].setPosition(left1);

	writing[17].setString("100\n");
	writing[17].setPosition(left2);

	writing[18].setString("150\n");
	writing[18].setPosition(left3);

	writing[19].setString("200\n");
	writing[19].setPosition(left4);

	writing[20].setString("300\n");
	writing[20].setPosition(130+right1);

	writing[21].setString("400\n");
	writing[21].setPosition(130+right2);

	writing[22].setString("500\n");
	writing[22].setPosition(130+right3);

	writing[23].setString("INNA KWOTA\n");
	writing[23].setPosition(50+right4);

	writing[24].setString("PROSZE ODEBRAC KARTE");
	writing[24].setPosition(230,250);

	writing[25].setString("   DZIEKUJEMY\nI ZAPRASZAMY PONOWNIE");
	writing[25].setPosition(250, 250);

}
Atm::~Atm() {
	//delete word;
}

void Atm::drawInfo(RenderWindow& window) {
	for (int i = 0; i < Max_atm; i++)
	{
		window.draw(word[i]);
	}
}

void Atm::setInfo(std::string card_nr, std::string pin, std::string balance) {
	word[1].setString("Numer karty: " + card_nr);
	word[2].setString("Stan konta: " + balance);
	word[3].setString("PIN: " + pin);
}

void Atm::setInfo(std::string dycha, std::string dwie, std::string piec, std::string sto, std::string dwiescie, std::string piecset) {

}

void Atm::setCardIn(RenderWindow& window) {
	cardIn.setSize(Vector2f(140, 10));
	cardIn.setPosition(Vector2f(490.f, 505.f));
	cardIn.setFillColor(Color::Red);
	window.draw(cardIn);
}

void Atm::setCashIn(RenderWindow& window){
	paycheck2.setSize(Vector2f(220, 100));
	paycheck2.setPosition(Vector2f(450.f, 600.f));
	paycheckTexture2.loadFromFile("sbopen.png");
	paycheck2.setTexture(&paycheckTexture2);
	window.draw(paycheck2);
}

void Atm::draw_atm(RenderWindow& window) {
	//tlo bankomatu
	backAtm.setSize(Vector2f(700, 810));
	Atmtexture.loadFromFile("metal.png");
	backAtm.setTexture(&Atmtexture);
	window.draw(backAtm);

	//niebieski ekran
	screen.setSize(Vector2f(400, 400));
	screen.setFillColor(Color::Blue);
	screen.setPosition(Vector2f(150, 50));
	window.draw(screen);

	//tlo pod klawiature numeryczna
	backNum.setSize(Vector2f(300, 270));
	backNum.setPosition(Vector2f(100.f, 500.f));
	backNumberTexture.loadFromFile("sb2.png");
	backNum.setTexture(&backNumberTexture);
	window.draw(backNum);

	//otwor na karte
	lineCard.setSize(Vector2f(160, 8));
	lineCard.setPosition(Vector2f(480.f, 500.f));
	lineCard.setFillColor(Color::Black);
	window.draw(lineCard);

	//wyplata pieniedzy
	paycheck.setSize(Vector2f(220, 100));
	paycheck.setPosition(Vector2f(450.f, 600.f));
	paycheckTexture.loadFromFile("sb3.png");
	paycheck.setTexture(&paycheckTexture);
	window.draw(paycheck);

	// rysowanie przyciskow
	for (int i = 0; i < 21; i++)
	{
		buttons[i].drawTo(window);
	}
}

void Atm::Buttons() {
	font.loadFromFile("Anonymous_Pro_B.ttf");
	btnTexture1.loadFromFile("btn_texture1.png");
	//btnTexture2.loadFromFile("btn_texture2.png");
	btnTextureC.loadFromFile("btn_textureC.png");
	btnTextureE.loadFromFile("btn_textureE.png");
	btnTextureA.loadFromFile("btn_textureA.png");
	int n;
	for (int i = 1; i < 10; i++)
	{
		if (i < 4) {
			n = 1;
		}
		else if (i > 3 and i < 7) {
			n = 2;
		}
		else if (i > 6 and i < 10){
			n = 3;
		}
		buttons[i] = Button(std::string(1,'0' + i), Vector2f(50,50), 40, Color::Black, {float(110 + (i - 1) % 3 * 60), float(450 + 60*n)}, font, btnTexture1);//ilosc, char '0' to numer char w tabeli ascii, + 1 
	}
	buttons[0] = Button(std::string(1, '0'), Vector2f(50, 50), 40, Color::Black, { 170, 690 }, font, btnTexture1);
	buttons[18] = Button(std::string("C"), Vector2f(100, 50), 40, Color::Black, {290, 570}, font, btnTextureC);
	buttons[19] = Button(std::string("E"), Vector2f(100, 50), 40, Color::Black, {290, 630}, font, btnTextureE);
	buttons[20] = Button(std::string("A"), Vector2f(100, 50), 40, Color::Black, {290, 510}, font, btnTextureA);

	//buttons[21] = Button(std::string(" "), Vector2f(100, 50), 40, Color::Transparent, { 290, 630 }, font, btnTextureE);
	//buttons[22] = Button(std::string(" "), Vector2f(100, 50), 40, Color::Black, { 290, 630 }, font, btnTextureE);

	for (int i = 10; i < 18; i++) 
	{
		if (i > 9 and i < 14) {
			n = 0;
		}
		else if (i > 13 and i < 18) {
				n = 1;
		}
		buttons[i] = Button(std::string(1,' '), Vector2f(50, 50), 40, Color::Black, {float(80 + 490 * n), float(90 + (i - 2) % 4 * 90)}, font, btnTexture1);
	}
}

void Atm::dziekujemy(RenderWindow& window) {
	window.draw(writing[25]);
}

void Atm::odbierz_karte(RenderWindow& window) {
	window.draw(writing[24]);
}

void Atm::wloz_karte(RenderWindow& window){
		window.draw(writing[0]);
}
void Atm::wprowadz_pin(RenderWindow& window) {
		window.draw(writing[1]);
		window.draw(writing[8]);
}
void Atm::niepoprawny_pin(RenderWindow& window) {
	window.draw(writing[1]);
	window.draw(writing[8]);
}

void Atm::operacje(RenderWindow& window) {
	for (int i = 2; i <=5; i++)
	{
		window.draw(writing[i]);
	}
	window.draw(writing[10]);
}
void Atm::inna_kwota(RenderWindow& window) {
	window.draw(writing[12]);
	for (int i = 6; i <= 8; i++)
	{
		window.draw(writing[i]);
	}

}
void Atm::wyplata(RenderWindow& window) {
	for (int i = 14; i < 24; i++) {
		window.draw(writing[i]);
	}
	//window.draw(writing[12]);
}

void Atm::dostepne_srodki(RenderWindow& window) {
	window.draw(writing[9]);
	window.draw(writing[8]);
}

void Atm::zmiana_pin(RenderWindow& window) {
	window.draw(writing[1]);
	window.draw(writing[8]);
}

void Atm::potwierdz_pin(RenderWindow& window) {
	window.draw(writing[8]);
	window.draw(writing[13]);
}

void Atm::obsluga_przyciskow(RenderWindow& window, Event event) {
	if (screen_event == screen_e::dziekujemy and cash.isMouseOverOnCashhole(window, 450, 600, 670, 700)) {
		cash_in = false;
		screen_event = screen_e::wloz_karte;
	}
	for (int i = 0; i < 21; i++) {
		if (buttons[i].isMouseOver(window)) {
			//std::cout << i << std::endl;
			switch (screen_event) {
			case screen_e::wloz_karte:
				//card_in = false;
				helper = nic;
				break;
			case screen_e::wprowadz_pin:
				if (i <= 9 and i >= 0) {
					std::cout << i;
					dodaj_znak(i+'0');
					break;
				}
				switch(i){
				case 17:
					czysc_znaki();
					screen_event = screen_e::wloz_karte;
					break;
				case 18:
					usun_znak();
					break;
				case 19:
					if ((uzywana -> sprawdzPIN(wczytany)) == true) {
						uzywana -> setBalance(writing[9]);
						screen_event = screen_e::operacje;
						helper = helper_e::nic;
						czysc_znaki();
					}
					else {
						czysc_znaki();
					}
					break;
				}
				break;
			case screen_e::operacje:
				
				switch (i) {
				/*case 12:
					screen_event = 4;
					break;*/
				case 13:
					screen_event = screen_e::wyplata;
					break;
				case 15:
					card_in = false;
					czysc_znaki();
					screen_event = screen_e::wloz_karte;
					break;
				case 16:
					screen_event = screen_e::zmiana_pin;
					break;
				case 17:
					screen_event = screen_e::dost_srodki;
					break;
				}
				break;
			case screen_e::wyplata:
				switch (i) {
				case 10:
					czysc_znaki();
					wpisz_kwote('5');
					wpisz_kwote('0');
					for (int i = 0; i < 4; i++) {
						std::cout << wczytana_kwota[i];
					}
					std::cout << " PLN - ";
					break;
				case 11:
					czysc_znaki();
					wpisz_kwote('1');
					wpisz_kwote('0');
					wpisz_kwote('0');
					break;
				case 12:
					czysc_znaki();
					wpisz_kwote('1');
					wpisz_kwote('5');
					wpisz_kwote('0');
					break;
				case 13:
					czysc_znaki();
					wpisz_kwote('2');
					wpisz_kwote('0');
					wpisz_kwote('0');
					break;
				case 14:
					czysc_znaki();
					wpisz_kwote('3');
					wpisz_kwote('0');
					wpisz_kwote('0');
					break;
				case 15:
					czysc_znaki();
					wpisz_kwote('4');
					wpisz_kwote('0');
					wpisz_kwote('0');
					break;
				case 16:
					czysc_znaki();
					wpisz_kwote('5');
					wpisz_kwote('0');
					wpisz_kwote('0');
					break;
				case 17:
					czysc_znaki();
					screen_event = screen_e::inna_kwota;
					break;
				case 19:
					uzywana->wyplata(wczytana_kwota);
					uzywana->setBalance(writing[9]);
					break;
				case 20:
					czysc_znaki();
					screen_event = screen_e::operacje;
					break;
				}
				//cash.kwota_do_wydania();
				break;
			case screen_e::inna_kwota:
				if (i <= 9 and i >= 0) {
					std::cout << i;
					wpisz_kwote(i + '0');
					break;
				}
				switch (i) {
				case 15:
					uzywana->wyplata(wczytana_kwota);
					uzywana->setBalance(writing[9]);
					break;
				case 16:
					czysc_znaki();
					break;
				case 17:
					czysc_znaki();
					screen_event = screen_e::wyplata;
					break;
				case 18:
					usun_znak();
					break;
				case 19:
					uzywana->wyplata(wczytana_kwota);
					uzywana->setBalance(writing[9]);
					break;
				case 20:
					czysc_znaki();
					screen_event = screen_e::operacje;
					break;
				}
				break;
			case screen_e::zmiana_pin:
				if (i <= 9 and i >= 0) {
					std::cout << i;
					dodaj_znak(i+'0');
					break;
				}
				switch(i){
				case 17:
					czysc_znaki();
					screen_event = screen_e::operacje;
						break;
				case 18:
					usun_znak();
					break;
				case 19: 
					if (ilosc_z == 4) {
						for (int i = 0; i < 4; i++) {
							wczytany_temp[i] = wczytany[i];
						}
						czysc_znaki();
						screen_event = screen_e::potwierdz_pin;
					}
					else {
						czysc_znaki();
					}
					break;
				}
				break;
			case screen_e::dost_srodki:
				switch (i) {
				case 17:
					screen_event = screen_e::operacje;
					break;
				}
				break;
			case screen_e::potwierdz_pin:
				if (i <= 9 and i >= 0) {
					std::cout << i;
					dodaj_znak(i + '0');
					break;
				}
				switch (i) {
				case 17:
					czysc_znaki();
					screen_event = screen_e::operacje;
					break;
				case 18:
					usun_znak();
					break;
				case 19: // potwierdzamy 2 raz + wpisywanie nowego pinu do nazwy pliku
					if ((ilosc_z == 4 and uzywana->sprawdzZmienPIN(wczytany, wczytany_temp)) == true) {
						czysc_znaki();
						std::cout << "udalo sie\n";
						//metoda do zmiany pinu
						uzywana->zmienPIN(wczytany);
						screen_event = screen_e::operacje;
					}
					else {
						czysc_znaki();
						screen_event = screen_e::zmiana_pin;
						std::cout << "nie udalo sie\n";
					}
					break;
				}
				break;
			case screen_e::niepop_pin:
				break;
			case screen_e::dziekujemy:

				break;
			}
		}
	}
}

void Atm::dodaj_znak(char znak) {
	std::string star_pin = "WPROWADZ PIN:\n     ";
	std::string star_pin_zmien = "WPROWADZ PIN PONOWNIE:\n    ";
	if (ilosc_z < 4) {
		wczytany[ilosc_z] =  znak;
		ilosc_z += 1;
		for (int i = 0; i < ilosc_z; i++) {
			star_pin += '*';
			star_pin_zmien += '*';
		}
		writing[1].setString(star_pin);
		writing[13].setString(star_pin_zmien);
	}
}

void Atm::usun_znak() {
	std::string star_pin = "WPROWADZ PIN:\n     ";
	std::string star_pin_zmien = "WPROWADZ PIN PONOWNIE:\n    ";
	if (ilosc_z > 0) {
		ilosc_z --;
		for (int i = 0; i < ilosc_z; i++) {
			star_pin += '*';
			star_pin_zmien += '*';
		}
		writing[1].setString(star_pin);
		writing[12].setString(star_pin_zmien);
	}

	if (n_znak > 0) {
		std::string kwota = writing[12].getString();
		kwota.erase(kwota.size()-1, 1);
		n_znak--;
		writing[12].setString(kwota);
		//char nowa_wczytana_kwota[4];
		for (int i = n_znak; i < 4; i++) {
			wczytana_kwota[i] = '\0';
			//wczytana_kwota[i] = wczytana_kwota_temp[i];
			//std::cout << wczytana_kwota[i];
		}
		for (int i = 0; i < 4; i++) {
			std::cout << wczytana_kwota[i];
		}
	}
}

void Atm::czysc_znaki() {
	ilosc_z = 0;
	n_znak = 0;
	char nowa_wczytana_kwota[4];
	for (int i = 0; i < 4; i++) {
		wczytana_kwota[i] = '\0';
	}
	writing[1].setString("WPROWADZ PIN:\n     ");
	writing[12].setString("PODAJ KWOTE: \n    ");
	writing[13].setString("WPROWADZ PIN PONOWNIE:\n    ");
	writing[14].setString("WYBIERZ KWOTE\n  WYPLATY: ");
}

void Atm::wpisz_kwote(char znak) {
	std::string kwota = writing[12].getString();
	std::string kwota1 = writing[14].getString();
	if (n_znak < 4) {
		//wczytana_kw += znak;
		wczytana_kwota[n_znak] = znak;
		//wczytana_kwota_temp[n_znak] = znak;
		n_znak ++;
		kwota += znak;
		kwota1 += znak;
	}
	writing[12].setString(kwota);
	writing[14].setString(kwota1);
}