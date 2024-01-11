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
	sfilename = filename;
	pobierzDane(filename);
	std::string numer = filename.substr(filename.size() - 21, 16);
	cn = numer;
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
		pobierzDane(sfilename);
		std::cout << "\n\nNumer karty: " << sfilename << "\n";
		std::cout << "Stan konta: " << balance << "\n";
		std::cout << "blokada_dzienna: " << blokada_dzienna << "\n";
		std::cout << "stan_dziennej_wyplaty: " << stan_dziennej_wyplaty << "\n";
		std::cout << "Zostalo: " << ZostaloDzien() << "\n";
		std::cout << "blokada_miesieczna: " << blokada_miesieczna << "\n";
		std::cout << "stan_miesiecznej_wyplaty: " << stan_miesiecznej_wyplaty << "\n";
		std::cout << "Zostalo: " << ZostaloMiesiac() << "\n";
		std::cout << "Czy zablokowana: " << blockade << "\n";

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

void Card::pobierzDane(std::string filename) {
	std::ifstream file;
	file.open(filename);
	sfilename = filename;
	
	if (!file.is_open()) {
		std::cout << "Nie udalo sie otworzyc pliku!" << std::endl;
		return;
	}

	file >> balance >> blokada_dzienna >> stan_dziennej_wyplaty >> blokada_miesieczna >> stan_miesiecznej_wyplaty >> blockade;
	//std::cout << blokada_miesieczna << " " << blokada_dzienna << std::endl;
	std::cout << blockade;
	
}

void Card::zablokowanieKarty() {
	blockade = 1;
	std::ofstream zapis(sfilename);
	zapis << balance << "\n" << blokada_dzienna << " " << stan_dziennej_wyplaty << "\n" << blokada_miesieczna << " " << stan_miesiecznej_wyplaty << "\n" << blockade;
	zapis.close();
}

bool Card::blokada() {
	if (blockade == 1) {
		return true;
	}
	else {
		return false;
	}
}

//double Card::maksymalnaWyplataDzienna() {
//	return stan_dziennej_wyplaty;
//}
//double Card::maksymalnaWyplataMiesieczna() {
//	return stan_miesiecznej_wyplaty;
//}
double Card::ZostaloDzien() {
	double dostepneSaldo = blokada_dzienna - stan_dziennej_wyplaty;
	return dostepneSaldo;
}

double Card::ZostaloMiesiac() {
	double dostepneSaldo = blokada_miesieczna - stan_miesiecznej_wyplaty;
	return dostepneSaldo;
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

	srodki = balance - isr;
	double limitD = stan_dziennej_wyplaty + isr;
	double limitM = stan_miesiecznej_wyplaty + isr;
	std::cout << "\n" << stan_dziennej_wyplaty << " <-D stan starego limitu M-> " << stan_miesiecznej_wyplaty;
	std::cout << "\n" << isr << " <- wyplacana_kwota -> " << isr;
	std::cout << "\n" << limitD << " <-D stan nowego limitu M-> " << limitM;

	if (isr % 10 == 0 and balance >= isr) {
		if (limitD <= blokada_dzienna and limitM <= blokada_miesieczna) {
			cash.kwota_do_wydania(isr);
		}
		else {
			std::cout << "\nOsiagnieto limit dzienny lub miesieczny" << "\n";
			wydajemy = false;
		}
		
	}
	else {
		std::cout << "Brak srodkow na koncie lub podano nieodpowiednia kwote" << "\n";
		wydajemy = false;
	}

	if (wydajemy == true ) {
		
		//std::cout << ZostaloDzien() << " <- -> " << ZostaloMiesiac();
		std::ofstream zapis(sfilename);
		zapis << srodki << "\n" << blokada_dzienna << " " << limitD << "\n" << blokada_miesieczna << " " << limitM << "\n" << blockade;
		zapis.close();
		balance = srodki;

		std::string temp;
		temp += pin[0];
		temp += pin[1];
		temp += pin[2];
		temp += pin[3];
		bankomat.setInfo(card_nr.getString(), temp, std::to_string(balance));

		std::cout << "\nStan konta: " << balance << " PLN" << std::endl;
	}
	
}

