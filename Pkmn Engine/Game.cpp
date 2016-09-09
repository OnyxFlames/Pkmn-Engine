#include "Game.hpp"

#include <iostream> // For debugging. The base engine will not print to console in the end.

Game::Game(uint32_t width, uint32_t height, std::string title)
	: _window(sf::VideoMode(width, height), title), renderThread(&render, this)
{
	view.setCenter((float)width / 2, (float)height / 2);
	view.setSize(sf::Vector2f((float)width, (float)height));
	_window.setView(view);

	game_font.loadFromFile("../Resources/Fonts/Consola.ttf");
	sf::Text fps_text;

	fps_text.setFont(game_font);
	fps_text.setString("Initializing..");
	fps_text.setCharacterSize(10);
	//fps_text.setPosition((float)width / 2.25f, (float)height - 25);
	fps_text.setPosition((float)width / 2.5f, (float)height - 25);

	texts.push_back(std::make_unique<sf::Text>(fps_text));

	std::ifstream map_loc("../Resources/Maps/Test.map");

	Tilemap map(map_loc, 10, 10);
	map.reserve_memory();
	map.load();
	maps.push_back(std::make_unique<Tilemap>(map));

	_window.setActive(false);
	renderThread.launch();
}


Game::~Game()
{
}

void Game::run()
{
	sf::Time curr_time, prev_time, delta, best_delta = sf::microseconds(1000);
	sf::Clock base_clock, frame_clock;
	uint16_t best_framerate = 1;
	while (_window.isOpen())
	{
		curr_time = base_clock.getElapsedTime();
		// Count how many frames the engine can do a second.
		if (frame_clock.getElapsedTime().asSeconds() >= 1)
		{
			std::string fps_string = "FPS: " + std::to_string(framerate);
			if (delta.asMicroseconds() > 0)
			{
				fps_string += " | Delta: " + std::to_string(delta.asMicroseconds());
			}
			else
			{
				fps_string += " | Delta: PAUSED";
			}
			if (framerate > best_framerate)
				best_framerate = framerate;
			if (delta.asMicroseconds() < best_delta.asMicroseconds() && delta.asMicroseconds() != 0)
				best_delta = delta;
			fps_string += " | Best: " + std::to_string(best_framerate) + " - " + std::to_string(best_delta.asMicroseconds());

			texts[0]->setString(fps_string);
			framerate = 0;
			frame_clock.restart();
		}
		else
		{
			framerate++;
		}

		// Get the time since last frame.
		delta = (curr_time - prev_time);
		prev_time = curr_time;
		curr_time = base_clock.getElapsedTime();
		//prev_time = curr_time;
		if (is_paused)
			delta = sf::microseconds(0);
		handleInput();
		update(delta);
	}
}
void Game::handleInput()
{
	while (_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				_window.close();
			if (event.key.code == sf::Keyboard::Tilde)
				is_paused = !is_paused;
			
			if (event.key.code == sf::Keyboard::W)
				m_up = true;
			if (event.key.code == sf::Keyboard::D)
				m_right = true;
			if (event.key.code == sf::Keyboard::S)
				m_down = true;
			if (event.key.code == sf::Keyboard::A)
				m_left = true;
			// set movement flags
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::W)
				m_up = false;
			if (event.key.code == sf::Keyboard::D)
				m_right = false;
			if (event.key.code == sf::Keyboard::S)
				m_down = false;
			if (event.key.code == sf::Keyboard::A)
				m_left = false;
			// unset movement flags
			break;
		}
	}
}
void Game::update(sf::Time delta)
{
	if (sprites.size() == 0)
		return;
	if (m_up)
		sprites[0]->move(0.0f, -(player_speed * delta.asMicroseconds()));
	if (m_right)
		sprites[0]->move((player_speed * delta.asMicroseconds()), 0.0f);
	if (m_down)
		sprites[0]->move(0.0f, (player_speed * delta.asMicroseconds()));
	if (m_left)
		sprites[0]->move(-(player_speed * delta.asMicroseconds()), 0.0f);
}
void render(Game *game)
{
	/*
	TODO: Get sf::View working so the window doesnt default and has a proper view window.

	TODO2: Implement a swap for resource vectors so that when a new scene needs to be loaded, the engine will populate a vector with the new resources, then at the time of loading, swap them,
	then clean out the old vector if necessary.
	*/
	while (game->get_window().isOpen())
	{
		game->get_window().clear();
		for (std::unique_ptr<sf::Sprite> &draw : game->get_sprites())
			game->get_window().draw(*draw);
		for (std::unique_ptr<sf::Text> &draw : game->get_texts())
			game->get_window().draw(*draw);
		for (std::unique_ptr<Tilemap> &draw : game->get_maps())
			;/*if (draw != nullptr)
				game->_window.draw(*draw);*/	// TODO: flesh out tilemaps
		game->get_window().display();
	}
}

void Game::load(sf::Sprite &sprite)
{
	sprites.push_back(std::make_unique<sf::Sprite>(sprite));
}