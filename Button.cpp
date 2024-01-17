#include "Button.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>

using namespace sf;

Button::Button(std::string t, Vector2f size, int charSize, Color textColor, Vector2f pos, Font &font, Texture &texture) {
	
	button.setPosition(pos);
	button.setSize(size);
	button.setTexture(&texture);

	float xPos = (pos.x + button.getGlobalBounds().width / 2) - (button.getGlobalBounds().width / 0, 7);
	float yPos = (pos.y + button.getGlobalBounds().height / 2) - (button.getGlobalBounds().height / 2);
	text.setString(t);
	text.setFillColor(textColor);
	text.setFont(font);
	text.setCharacterSize(charSize);
	text.setPosition({ xPos, yPos });
}

void Button::setBackTexture(Texture& texture) {
	button.setTexture(&texture);
}

void Button::setTextColor(Color color) {
	text.setFillColor(color);
}

void Button::drawTo(RenderWindow& window) {
	window.draw(button);
	window.draw(text);
}

bool Button::isMouseOver(RenderWindow& window) {
	int mouseX = Mouse::getPosition(window).x;
	int mouseY = Mouse::getPosition(window).y;

	float btnPosX = button.getPosition().x;
	float btnPosY = button.getPosition().y;

	float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
	float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

	if (mouseX < btnxPosWidth and mouseX > btnPosX and mouseY < btnyPosHeight and mouseY > btnPosY) {
		return true;
	}
	return false;
}