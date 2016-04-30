#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <memory>
#include <string>
#include <map>

namespace Textures
{
	enum ID 
	{
		Test,
		Player,
		GrassTile,
		DirtTile,
	};
}

class TextureManager
{
private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> texture_map;
public:
	TextureManager();
	void load(Textures::ID id, std::string &file_name);
	sf::Texture& get(Textures::ID id) const;
	size_t get_size() const;
	~TextureManager();
};

#endif
