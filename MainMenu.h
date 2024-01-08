#pragma once
#include <SFML/Graphics.hpp> 
#include <iostream> 

//using namespace std;
using namespace sf;

#define Max_main_menu 4

enum menu_e
{
	mMenu, start, informacje, opcje, wyjscie
};

class MainMenu
{
public:
	MainMenu(RenderWindow& window_d);

	void draw(RenderWindow& window, float width, float height);
	//void draw_back(RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int MainMenuPressed() {
		return MainMenuSelected;
	}
	~MainMenu();
private:
	RenderWindow& window;
	int MainMenuSelected;
	Font font;
	Text mainMenu[Max_main_menu];
};

