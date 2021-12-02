#pragma once

#include "NuEntity.hpp"
#include "Particle.hpp"

class Game {
public:
	static int			shake;
	NuEntity*			player;
	static Particle		parts;
	static void			particlesAt(sf::Vector2f pos);
};