#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity
{
private:
	bool moving_up = false, moving_right = false, moving_down = false, moving_left = false;
	sf::Sprite sprite;
	sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f);
public:
	Entity();
	~Entity();

	sf::Vector2f getVelocity() const;
	void		 setVelocity(sf::Vector2f _velocity);
};

#endif