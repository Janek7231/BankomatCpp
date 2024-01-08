#include "MainMenu.h"

MainMenu::MainMenu(RenderWindow& window_d) 
	: window(window_d)
{
	if (!font.loadFromFile("Anonymous_Pro_B.ttf")) 
	{
		std::cout << "Nie znaleziono czcionki" << std::endl;
	}
	float width = window.getSize().x;
	float height = window.getSize().y;

	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::White);
	mainMenu[0].setString("Bankomat");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(width / 2 - 160,200);

	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setString("Opcje");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(width / 2 - 100, 300);

	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::White);
	mainMenu[2].setString("Informacje");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(width / 2 - 200, 400);

	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(Color::White);
	mainMenu[3].setString("Wyjscie");
	mainMenu[3].setCharacterSize(70);
	mainMenu[3].setPosition(width / 2 - 135, 500);

	MainMenuSelected = -1;
}
MainMenu::~MainMenu() {
	//delete mainMenu;
}

void MainMenu::draw(RenderWindow& window, float width, float height) {
	RectangleShape background;
	background.setSize(Vector2f(width, height));
	Texture Maintexture;
	Maintexture.loadFromFile("banknotyMenu.png");
	background.setTexture(&Maintexture);
	window.draw(background);


	for (int i = 0; i < Max_main_menu; i++) 
	{
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveUp() {
	if (MainMenuSelected < 0)
	{
		MainMenuSelected = 3;
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
	else if (MainMenuSelected == 0)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected = 3;
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
	else if (MainMenuSelected == 1)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected--;
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
	else if (MainMenuSelected == 2)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected--;
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
	else
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected--;
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}

void MainMenu::MoveDown() {
	if (MainMenuSelected < 0)
	{
		MainMenuSelected = 0;
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
	else if (MainMenuSelected == 0)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected = 1;
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
	else if (MainMenuSelected == 1)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected++;
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
	else if (MainMenuSelected == 2)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected++;
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
	else
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected = 0;
		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}