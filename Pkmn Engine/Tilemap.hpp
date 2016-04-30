#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <string>
#include <cstdint>
#include <fstream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "TextureManager.hpp"

class Tilemap
{
private:
	std::string d_map_name; // The name of the map stored internally.
	uint16_t map_width, map_height;
	uint8_t tile_size = 16;
	std::vector<
		std::vector<uint16_t>> map;	// The first vector is the X axis of a map, the second is the y axis.
	std::ifstream *map_file;
	TextureManager *texturemanager_ptr = nullptr;
public:
	Tilemap(std::ifstream &_map_file, uint16_t _width, uint16_t _height);
	//Tilemap(const std::string &file_name, uint16_t _width, uint16_t _height);
	bool register_texturemanager(TextureManager &text_man);
	void reserve_memory();
	void load();
	sf::Image draw();
	sf::Image stitch_tilemap();
	~Tilemap();


	void debug_unroll_map();

};

#endif