#pragma once
#include <SFML\Graphics.hpp>

class Ray
{
public:
	Ray();
	Ray(sf::Vector2f);
	~Ray();

	static struct Colide {
		bool isCollide;
		sf::Vector2f position;
		sf::VertexArray* object;
		float distance;
	};

	float distanceTo(sf::Vector2f);
	Colide cast(sf::VertexArray&);
	Colide cast_closest(std::vector<sf::VertexArray>&);
	void move(sf::Vector2f);
	void rotate(sf::Vector2f);
	void draw(sf::RenderTarget&);
	sf::Vector2f cast_end;

private:
	sf::Vector2f direction;
	sf::Vector2f position;
	
	sf::VertexArray line;
	float length;

	bool colided;
};

