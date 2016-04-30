#include "Tilemap.hpp"

#include <cctype>
#include <iostream>

Tilemap::Tilemap(std::ifstream &_map_file, uint16_t _width, uint16_t _height)
	: map_width(_width), map_height(_height)
{
	map_file = &_map_file;
	//map_file->open(file_name);
	if (!map_file->is_open())
		std::cerr << "Map loading error: map does not exist!\n";
}

bool Tilemap::register_texturemanager(TextureManager &text_man)
{
	texturemanager_ptr = &text_man;
	return (texturemanager_ptr != nullptr);
}

sf::Image Tilemap::stitch_tilemap()
{
	std::cout << "TODO: After tilemap is worked on, add stitch_tilemap() functionality." << std::endl;
	return sf::Image();
}

void Tilemap::reserve_memory()
{
	/*
		This function stretches the 2D vector of 'tiles' to the width, and the 'height' er, length of the map.
	*/
	map.resize(map_width);
	for (auto &_map : map)
	{
		_map.resize(map_height);
	}
}
void Tilemap::load()
{
	std::string buffer = "\0";
	for (uint16_t i = 0; i < map_width; i++)
	{
		for (uint16_t j = 0; j < map_height; j++)
		{
			*map_file >> buffer;
			//std::cout << "buffer: [\t" << buffer << "\t]\n";
			for(char c : buffer)
				if (!isdigit(c))
					buffer = "-1";
			map[i][j] = std::stoi(buffer);
		}
	}
}

sf::Image Tilemap::draw() 
{
	/*
		TODO: Have the draw() function generate an image if not generated, and if generated, return that image for it to be drawn.
		This will be used within the engine's core, where it will call the draw function of every tilemap is has access to on runtime.

		Note: This is definitely not the most optimal way. Find a better one.
	*/
	for (auto &_map : map)
		for (auto &__map : _map)
			std::cout << __map << " ";
	return sf::Image();
}

void Tilemap::debug_unroll_map()
{
	for (auto &_map : map)
		for (auto &__map : _map)
			std::cout << __map << " ";
}

Tilemap::~Tilemap()
{
}

