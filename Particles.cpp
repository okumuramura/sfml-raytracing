#include "Particles.h"
#include "Ray.h"
#include <math.h>
#include <iostream>

const float TWO_PI = 6.28318530718;

Particles::Particles()
{
	this->ray_count = 1000;
	this->position = sf::Vector2f(0.f, 0.f);
	this->initRays(this->ray_count);

}

Particles::Particles(int x, int y, unsigned int count) {
	this->ray_count = count;
	this->position = position;
	this->initRays(count);
}


Particles::~Particles()
{
	delete[] this->rays;
}

void Particles::initRays(unsigned int count) {
	this->rays = new Ray[count];
	float step = TWO_PI / count;
	Ray* ray_ptr;
	for (int a = 0; a < count; a++) {
		ray_ptr = new Ray(sf::Vector2f(std::cosf(step * a), std::sinf(step * a)));
		ray_ptr->move(this->position);
		this->rays[a] = *ray_ptr;
	}
}

void Particles::move(sf::Vector2f pos) {
	this->position = pos;
	for (int i = 0; i < this->ray_count; i++) {
		this->rays[i].move(pos);
	}
}

void Particles::cast(sf::VertexArray& object) {
	this->colide_points.clear();
	Ray::Colide colide;
	for (int i = 0; i < this->ray_count; i++) {
		colide = this->rays[i].cast(object);
		if (colide.isCollide) {
			this->colide_points.push_back(colide.position);
		}
	}
}

void Particles::cast_to_all(std::vector<sf::VertexArray>& objects) {
	this->colide_points.clear();
	Ray::Colide colide;
	for (int i = 0; i < this->ray_count; i++) {
		colide = this->rays[i].cast_closest(objects);
		if (colide.isCollide) {
			this->colide_points.push_back(colide.position);
		}
	}
}

void Particles::draw(sf::RenderTarget& window) {
	
	for (int i = 0; i < this->ray_count; i++) {
		this->rays[i].draw(window);
	}
}

void Particles::draw_shape(sf::RenderTarget& window) {
	sf::ConvexShape light(this->ray_count);
	light.setFillColor(sf::Color(255, 255, 180, 255));

	for (int i = 0; i < this->ray_count; i++) {
		light.setPoint(i, this->rays[i].cast_end);
	}
	window.draw(light);
}