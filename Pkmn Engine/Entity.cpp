#include "Entity.hpp"



Entity::Entity()
{
}


Entity::~Entity()
{
}

sf::Vector2f Entity::getVelocity() const
{
	return velocity;
}
void		 Entity::setVelocity(sf::Vector2f _velocity)
{
	velocity = _velocity;
}