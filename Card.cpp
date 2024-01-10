#include <SFML/Graphics.hpp> 
#include <iostream> 
#include <fstream> 
#include <cstdio> 
#include "Card.h"
#include "Cash.h"
#include "Atm.h"
#include <fstream>
#include <string>

extern Cash cash;
extern bool card_in;
extern bool wydajemy;

Card::Card(std::string filename, Font& font, Texture& texture, Vector2f pos)
{
	std::ifstream file;
	file.open(filename);
	sfilename = filename;
	std::string numer = filename.substr(filename.size() - 21, 16);
	cn = numer;
	if (!file.is_open()) {
		std::cout << "tarapaty" << std::endl;
		return;
	}

	file >> balance;
	for (int i = 0; i < 4; i++) {
		pin[i] = filename[filename.size() - 4 + i];
	}

	card.setTexture(texture);
	card.setScale(0.75, 0.75);
	card.setPosition(pos);

	card_nr.setString(numer);
	card_nr.setPosition(pos + sf::Vector2f(50,93));
	card_nr.setFont(font);
	card_nr.setCharacterSize(37);
	card_nr.setFillColor(Color::White);
	card_nr.setScale(0.5, 0.5);
	
}

void Card::drawCard(RenderWindow& window) {
	window.draw(card);
	window.draw(card_nr);
}

extern Atm bankomat;

bool Card::isMouseOver(RenderWindow& window) {
	int mouseX = Mouse::getPosition(window).x;
	int mouseY = Mouse::getPosition(window).y;

	float btnPosX = card.getPosition().x;
	float btnPosY = card.getPosition().y;

	float btnxPosWidth = card.getPosition().x + card.getLocalBounds().width;
	float btnyPosHeight = card.getPosition().y + card.getLocalBounds().height;

	if (mouseX < btnxPosWidth and mouseX > btnPosX && mouseY < btnyPosHeight and mouseY > btnPosY) {
		std::string temp;
		temp += pin[0];
		temp += pin[1];
		temp += pin[2];
		temp += pin[3];
		bankomat.setInfo(card_nr.getString(),temp,std::to_string(balance));
		card_in = true;
		return true;
	}
	return false;
}

bool Card::isMouseOverOnCardhole(RenderWindow& window) {
	int mouseX = Mouse::getPosition(window).x;
	int mouseY = Mouse::getPosition(window).y;

	float btnPosX = 450;
	float btnPosY = 490;

	float btnxPosWidth = 670;
	float btnyPosHeight = 520;

	if (mouseX < btnxPosWidth and mouseX > btnPosX && mouseY < btnyPosHeight and mouseY > btnPosY) {
		return true;
	}
	return false;
}

bool Card::sprawdzPIN(char* wczytany) {
	for (int i = 0; i < 4; i++) {
		if (wczytany[i] != pin[i]) {
			return false;
		}
	}
	return true;
}

void Card::zmienPIN(char* wczytany) {
	std::string oldname = sfilename;
	std::string newname = "karty/" + cn + ".";
	for (int i = 0; i < 4; i++) {
		pin[i] = wczytany[i];
		newname += wczytany[i];
	}

	std::string temp;
	temp += pin[0];
	temp += pin[1];
	temp += pin[2];
	temp += pin[3];
	bankomat.setInfo(card_nr.getString(), temp, std::to_string(balance));

	if (std::rename(oldname.c_str(), newname.c_str()))
	{
		std::perror("Error renaming");
	}
	else
		std::cout << "File moved successfully";
}

bool Card::sprawdzZmienPIN(char* wczytany, char* wczytany_temp) {
	for (int i = 0; i < 4; i++) {
		if (wczytany[i] != wczytany_temp[i]) {
			return false;
		}
	}
	return true;
}

void Card::setBalance(sf::Text &writing) {
	writing.setString("DOSTEPNE SRODKI:\n   " + std::to_string(balance));
}

void Card::wyplata(char* wyp) {
	float srodki = 0;
	int isr = 0;
	std::string sr;

	for (int i = 0; i < sizeof(wyp); i++) {
		sr += wyp[i];
	}
	isr = std::stof(sr);
	if (isr % 10 == 0 and balance >= isr) {
		cash.kwota_do_wydania(isr);
	}
	else {
		wydajemy = false;
	}

	if (wydajemy == true ) {
		srodki = balance - isr;
		std::ofstream zapis(sfilename);
		zapis << srodki;
		zapis.close();
		balance = srodki;

		std::string temp;
		temp += pin[0];
		temp += pin[1];
		temp += pin[2];
		temp += pin[3];
		bankomat.setInfo(card_nr.getString(), temp, std::to_string(balance));

		std::cout << balance << " PLN" << std::endl;
	}
	
}

