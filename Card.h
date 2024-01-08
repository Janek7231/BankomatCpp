#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class Card
{
private:
	char pin[4];
	char zmien_pin[4];
	char temp_pin[4];
	long double balance;
	Sprite card;
	Text card_nr;
	std::string cn;
	std::string sfilename;
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
	//void wplata(char *wp);
};



