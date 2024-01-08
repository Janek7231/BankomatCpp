#pragma once
#include <SFML/Graphics.hpp> 
#include <iostream> 
#include "Button.h"

//using namespace std;
using namespace sf;

#define Max_atm 4
#define Writings 30

#define left1 150, 80
#define left2 150, 190
#define left3 150, 280
#define left4 150, 370
#define right1 360, 80
#define right2 360, 190
#define right3 360, 280
#define right4 360, 370
extern int screen_event;

enum screen_e
{
	wloz_karte, wprowadz_pin, operacje, wyplata, inna_kwota, zmiana_pin, dost_srodki, potwierdz_pin, niepop_pin, dziekujemy, odbierz_karte
};

enum helper_e
{
	nic, karty, banknoty
};

class Atm
{
public:
	Atm(RenderWindow& window_d, float width, float height);
	void drawInfo(RenderWindow& window);
	void draw_atm(RenderWindow& window);
	void Buttons();
	/*int AtmPressed() {
		return AtmSelected;
	}
	*/
	~Atm();

	void wloz_karte(RenderWindow& window);
	void wprowadz_pin(RenderWindow& window);
	void niepoprawny_pin(RenderWindow& window);
	void operacje(RenderWindow& window);
	void inna_kwota(RenderWindow& window);
	void wyplata(RenderWindow& window);
	void dostepne_srodki(RenderWindow& window);
	void zmiana_pin(RenderWindow& window);
	void potwierdz_pin(RenderWindow& window);
	void odbierz_karte(RenderWindow& window);
	void dziekujemy(RenderWindow& window);
	//void czy_chcesz(RenderWindow& window);
	//void brak_zasobow(RenderWindow& window);
	void obsluga_przyciskow(RenderWindow& window, Event event);

	void setInfo(std::string card_nr, std::string pin, std::string balance);
	void setInfo(std::string dycha, std::string dwie, std::string piec, std::string sto, std::string dwiescie, std::string piecset);
	void setCardIn(RenderWindow& window);
	void setCashIn(RenderWindow& window);
	

	void dodaj_znak(char znak);
	void usun_znak();
	void czysc_znaki();
	void wpisz_kwote(char znak);
private:
	Button buttons[30];
	//int AtmSelected;
	Font font;
	Texture btnTexture1;
	Texture btnTextureE;
	Texture btnTextureC;
	Texture btnTextureA;
	Text word[Max_atm];
	Text writing[Writings];

	RectangleShape backAtm;
	RectangleShape screen;
	RectangleShape backNum;
	RectangleShape lineCard;
	RectangleShape cardIn;
	RectangleShape paycheck;
	RectangleShape paycheck2;
	Texture backNumberTexture;
	Texture paycheckTexture;
	Texture paycheckTexture2;
	Texture Atmtexture;

	char wczytany[4];
	char wczytany_temp[4];
	char wczytana_kwota[4];
	std::string wczytana_kw;
	char wczytana_kwota_temp[4];
	int ilosc_z = 0;
	int n_znak = 0;
	float ikwota = 0;
};
