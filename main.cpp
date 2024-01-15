#include "MainMenu.h"
#include "Atm.h"
#include "Button.h"
#include "Card.h"
#include "Cash.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>
#include <filesystem>
#include <cmath>

using namespace sf;
namespace fs = std::filesystem;
//using namespace std;

std::vector<Card>cards;//tablica dynamiczna typu card

const int x = 1440; //16*80=1280   16*90=1440 
const int y = 810; // 9*80=720   9*90=810
int stage = 1;
int screen_event = wloz_karte;
extern int helper = nic;
extern bool card_in = false;
extern bool cash_in = false;
extern bool wydajemy;
extern Card* uzywana = nullptr;
Cash cash;

RenderWindow window(VideoMode(x, y), "Bankomat", Style::Titlebar);
MainMenu menu(window);
Atm bankomat(window, x, y);

void drawStage(int stage) {
	switch (stage)
	{
	case mMenu:
		menu.draw(window, x, y);
		break;
	case start:
		bankomat.draw_atm(window);
		if (card_in == true) {
			bankomat.setCardIn(window);
		}
		if (cash_in == true) {
			bankomat.setCashIn(window);
		}
		switch (helper)
		{
		case nic:

			break;
		case karty:
			bankomat.drawInfo(window);
			for (int i = 0; i < cards.size();i++) {
				cards[i].drawCard(window);
			}
			break;
		case banknoty:
			break;
		}

		switch (screen_event)
		{ 
		case wloz_karte:
			bankomat.wloz_karte(window);
			break;
		case odbierz_karte:
			bankomat.odbierz_karte(window);
			break;
		case wprowadz_pin:
			bankomat.wprowadz_pin(window);
			break;
		case operacje:
			bankomat.operacje(window);
			break;
		case wyplata:
			bankomat.wyplata(window);
			break;
		case inna_kwota:
			bankomat.inna_kwota(window);
			break;
		case zmiana_pin:
			bankomat.zmiana_pin(window);
			break;
		case dost_srodki:
			bankomat.dostepne_srodki(window);
			break;
		case potwierdz_pin:
			bankomat.potwierdz_pin(window);
			break;
		case niepop_pin:
			bankomat.niepoprawny_pin(window);
			break;
		case dziekujemy:
			bankomat.dziekujemy(window);
			break;
		case karta_zablokowana:
			bankomat.karta_zablokowana(window);
			break;
		case osiagnieto_limit:
			bankomat.osiagnieto_limit(window);
			break;
		}
		break;
	case informacje:
		break;
	case opcje:

		break;
	default:
		break;
	}
}

void updateInput() {
	
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
		}
		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::Escape && stage == mMenu)
			{
				window.close();
			}
			if (event.key.code == Keyboard::Escape && stage != mMenu)
			{
				//stage = mMenu;
				window.close();
			}
			if (event.key.code == Keyboard::Up)
			{
				menu.MoveUp();
			}
			if (event.key.code == Keyboard::Down)
			{
				menu.MoveDown();
			}
			if (event.key.code == Keyboard::Return)
			{

				int x = menu.MainMenuPressed();
				switch (x) {
				case 0:
					stage = start;//start (bankoamt)
					break;
				case 1:
					stage = informacje;//informacje
					break;
				case 2:
					stage = opcje;//opcje
					break;
				case 3:
					window.close();
					break;
				}
			}
		}
		if (event.type == Event::MouseButtonPressed and stage == start)
		{
			/*int mouseX = Mouse::getPosition(window).x;
			int mouseY = Mouse::getPosition(window).y;
			std::cout << "x: " << mouseX << ", y: " << mouseY << "\n";*/

			bankomat.obsluga_przyciskow(window, event);

			for (auto &card : cards) {// card to ka¿dy indeks tablicy ":" dzia³a jak "in"
				if (card.isMouseOver(window)) {
					uzywana = &card;
					if (screen_event == wloz_karte){
						if (card.blokada() == false) {
							screen_event = wprowadz_pin;
						}
						else {
							screen_event = karta_zablokowana;
						}

					}
					break;
				}
				if (card.isMouseOverOnCardhole(window) and screen_event == odbierz_karte) {
					if (wydajemy == true) {
						//helper = nic;
						card_in = false;
						screen_event = dziekujemy;
						cash_in = true;
					}
					else if (wydajemy == false){
						//helper = nic;
						card_in = false;
						cash_in = false;
						screen_event = wloz_karte;
					}
				}
				else if (card.isMouseOverOnCardhole(window) and screen_event == karta_zablokowana) {
					helper = nic;
					card_in = false;
					screen_event = wloz_karte;
				}
				else if (card.isMouseOverOnCardhole(window) and screen_event == wloz_karte) {
					helper = karty;
				}
			}
		}
	}
}
	
void main() {
	bankomat.Buttons();
	Font font;
	font.loadFromFile("Anonymous_Pro.ttf");
	Texture card1;
	card1.loadFromFile("karta_red.png");


	int i = 0;
	for (auto next : fs::directory_iterator("karty/")){
		cards.emplace_back(next.path().string(), font, card1, sf::Vector2f(750+(300*(i%2)), 200+(200* floor(i/2))));
		i++;
	}
	window.setSize(sf::Vector2u(1440 / 2 - 20, 810));
	sf::View widok(sf::FloatRect(0, 0, 1440 / 2 - 20, 810));
	window.setView(widok);
	window.setFramerateLimit(40);
	while (window.isOpen())
	{
		updateInput();

		window.clear(Color::Black);
		drawStage(stage);
		window.display();
	}
}