#pragma once
#include <SFML\Graphics.hpp>
#include "Ray.h"

class Particles
{
public:
	Particles();
	Particles(int, int, unsigned int);
	void move(sf::Vector2f);
	void draw(sf::RenderTarget&);
	void draw_shape(sf::RenderTarget&);
	void cast(sf::VertexArray&);
	void cast_to_all(std::vector<sf::VertexArray>&);
	~Particles();
private:
	sf::Vector2f position;
	Ray* rays;
	unsigned int ray_count;
	void initRays(unsigned int);
	std::vector<sf::Vector2f> colide_points;
};

