#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::Left,
	Keyboard::Right,
};

sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship *> ships;

const int gameWidth = 800;
const int gameHeight = 600;

void Load(){
	if(!spritesheet.loadFromFile("res/img/invaders_sheet.png")){
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(32, 32)));
}

void Render(RenderWindow &window){
	window.draw(invader);
}

void Update(RenderWindow &window){
	if(Keyboard::isKeyPressed(Keyboard::Escape)){
		window.close();
	}
}



int main(){
  sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Space Invaders");

  while (window.isOpen()){
    window.clear();
	Update(window);
	Render(window);
    window.display();
  }
  return 0;
}