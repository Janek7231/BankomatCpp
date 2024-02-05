#pragma once
#include <SFML/Graphics.hpp> 
#include <iostream> 
#include "Button.h"

//using namespace std;
using namespace sf;

#define Max_atm 4
#define Writings 35

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
	wloz_karte, wprowadz_pin, operacje, wyplata, inna_kwota, zmiana_pin, dost_srodki, potwierdz_pin, niepop_pin, dziekujemy, odbierz_karte, karta_zablokowana, osiagnieto_limit
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
	void karta_zablokowana(RenderWindow& window);
	void dziekujemy(RenderWindow& window);
	void osiagnieto_limit(RenderWindow& window);
	void obsluga_przyciskow(RenderWindow& window, Event event);

	void potwierdzenieDraw(RenderWindow& window);
	void wypiszNominaly(int ilosc, int nominal);
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
	RectangleShape receipt;
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

	int proby = 0;
};
