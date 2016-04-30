#include "TextureManager.hpp"

#include <iostream>

TextureManager::TextureManager()
{
}

void TextureManager::load(Textures::ID id, std::string &file_name)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	texture->loadFromFile(file_name);
	texture_map.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture& TextureManager::get(Textures::ID id) const
{
	auto found = texture_map.find(id);
	return *found->second;
}

size_t TextureManager::get_size() const
{
	return texture_map.size();
}

TextureManager::~TextureManager()
{
}