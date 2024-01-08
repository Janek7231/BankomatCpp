#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

using namespace sf;
//using namespace std;

//#define Number_of_buttons 19

class Button
{
public:
	Button() {}

	Button(std::string t, Vector2f size, int charSize, Color textColor, Vector2f pos, Font& font, Texture &texture);
	void setBackTexture(Texture& texture);
	void setTextColor(Color color);
	void drawTo(RenderWindow& window);
	bool isMouseOver(RenderWindow& window);
	//bool isClicked();
;
private:
	RectangleShape button;
	Text text;
};


