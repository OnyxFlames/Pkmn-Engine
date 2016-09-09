#include <iostream>
#include <fstream>

#include "Game.hpp"

int main(int argc, char* argv[])
{
	sf::Texture texture;
	texture.loadFromFile("../Resources/Textures/face.png");
	sf::Sprite test;
	test.setTexture(texture);

	Game game(1280, 720, "Pkmn Engine");
	game.load(test);
	game.run();

	return 0;
}