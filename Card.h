#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class Card
{
private:
	struct Data {
		int rok;
		int miesiac;
		int dzien;
	};
	char pin[4];
	char zmien_pin[4];
	char temp_pin[4];
	long double balance;
	double blokada_dzienna;
	double stan_dziennej_wyplaty;
	double blokada_miesieczna;
	double stan_miesiecznej_wyplaty;
	int blockade;
	Sprite card;
	Text card_nr;
	std::string cn;
	std::string sfilename;

	std::string dataMies;
	std::string dataDzien;
	std::string dataTeraz;

	std::time_t czasTeraz;
	std::tm* lokalnyCzas;
public:
	Card(std::string filename, Font& font, Texture& texture, Vector2f pos);
	void drawCard(RenderWindow& window);
	bool isMouseOver(RenderWindow& window);
	bool isMouseOverOnCardhole(RenderWindow& window);
	bool sprawdzPIN(char* wczytany);
	void zmienPIN(char* wczytany);
	bool sprawdzZmienPIN(char *wczytany, char* wczytany_temp);
	void setBalance(sf::Text& writing);
	void wyplata(char *wyp);
	double maksymalnaWyplataDzienna();
	double maksymalnaWyplataMiesieczna();
	double ZostaloDzien();
	double ZostaloMiesiac();

	bool blokada();
	std::string obecnaData();
	void zapiszLimitDzienny(std::string dataDzisiaj, std::string dataDzien, std::string dataMiesiac);
	void zapiszLimitMiesieczny(std::string dataDzisiaj, std::string dataDzien, std::string dataMiesiac);
	void zablokowanieKarty();
	void pobierzDane(std::string filename, Data& dataD, Data& dataM, Data& dataT);
	void pobierzDane(std::string filename);
};



