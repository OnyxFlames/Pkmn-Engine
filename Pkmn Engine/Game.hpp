#ifndef GAME_HPP
#define GAME_HPP
#include <string>
#include <cstdint>
#include <vector>
#include <memory>

#include "Tilemap.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

class Game
{
private: 

	sf::RenderWindow _window;

	sf::Event event;
	sf::View view;
	
	std::vector<std::unique_ptr<sf::Sprite>> sprites;
	std::vector<std::unique_ptr<sf::Text>> texts;
	std::vector <std::unique_ptr<Tilemap>> maps;

	sf::Font game_font;
	sf::Thread renderThread;
	const float player_speed = 0.0005f;
	bool m_up = false, m_right = false, m_down = false, m_left = false;

	bool is_paused = false;
	uint32_t framerate = 0;
public:

	Game(uint32_t width, uint32_t height, std::string title);
	
	sf::RenderWindow &get_window() { return _window; }
	std::vector<std::unique_ptr<sf::Sprite>>& get_sprites() { return sprites; }
	std::vector<std::unique_ptr<sf::Text>>& get_texts() { return texts; }
	std::vector <std::unique_ptr<Tilemap>>& get_maps() { return maps; }


	void run();
	void update(sf::Time delta);
	void handleInput();
	void load(sf::Sprite &sprite);
	
	~Game();
};

void render(Game *game);

#endif