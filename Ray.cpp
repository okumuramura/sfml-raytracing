#include "Ray.h"
#include <SFML\Graphics.hpp>
#include <math.h>



Ray::Ray()
{
	this->length = 1000;
	this->position = sf::Vector2f(0.f, 0.f);
	this->direction = sf::Vector2f(1.f, 0.f);
	this->cast_end = this->position + this->direction * this->length;
	this->line = sf::VertexArray(sf::Lines, 2);
}

Ray::Ray(sf::Vector2f direction) {
	this->length = 1000;
	this->position = sf::Vector2f(0.f, 0.f);
	this->direction = direction;
	this->cast_end = this->position + this->direction * this->length;
	this->line = sf::VertexArray(sf::Lines, 2);
}


Ray::~Ray()
{
}

Ray::Colide Ray::cast(sf::VertexArray& object) {
	
	sf::Vector2f p1 = this->position;
	sf::Vector2f p2 = this->position + this->direction * this->length;
	sf::Vector2f p3, p4;
	unsigned int vertex_count = object.getVertexCount();
	float den;
	float t, u;
	bool colided = false;
	float min_distance = -1;
	float distance;

	for (int v = 0; v < vertex_count; v++) {
		p3 = object[v].position;
		p4 = (v == vertex_count - 1) ? (object[0].position) : (object[v + 1].position);
		den = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
		if (den == 0) continue;
		t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / den;
		u = -((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / den;

		if (t > 0 && t < 1 && u > 0 && u < 1) {
			sf::Vector2f end_point(p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y));
			colided = true;
			distance = this->distanceTo(end_point);
			if (min_distance == -1) min_distance = distance;
			if (distance <= min_distance) {
				min_distance = distance;
				this->cast_end = end_point;
			}
		}
	}
	this->colided = colided;
	Ray::Colide colide;
	colide.isCollide = colided;
	colide.position = this->cast_end;
	colide.object = &object;
	colide.distance = std::sqrtf(min_distance);
	return colide;

}

Ray::Colide Ray::cast_closest(std::vector<sf::VertexArray>& objects) {
	float min_distance = -1;
	float distance;
	bool colided = false;
	Ray::Colide colide;
	Ray::Colide res;

	for (sf::VertexArray& obj : objects) {
		colide = this->cast(obj);
		if (colide.isCollide) {
			colided = true;
			distance = colide.distance;
			if (min_distance == -1) min_distance = distance;
			if (distance <= min_distance) {
				min_distance = distance;
				res.position = colide.position;
				res.object = &obj;
			}
		}
	}
	if (colided) this->cast_end = res.position;
	this->colided = colided;
	res.isCollide = colided;
	res.position = this->cast_end;
	res.distance = min_distance;
	return res;
	
}

void Ray::move(sf::Vector2f pos) {
	this->position = pos;
	this->cast_end = this->position + this->direction * this->length;
}

void Ray::rotate(sf::Vector2f dir) {
	this->direction = dir;
	this->cast_end = this->position + this->direction * this->length;
}

float Ray::distanceTo(sf::Vector2f point) {
	return (point.y - this->position.y) * (point.y - this->position.y) + (point.x - this->position.x) * (point.x - this->position.x);
}

void Ray::draw(sf::RenderTarget& window) {
	this->line[0].position = this->position;
	this->line[1].position = this->cast_end;
	if (this->colided){
		this->line[0].color = sf::Color(255, 255, 180, 30);
		this->line[1].color = sf::Color(255, 255, 180, 30);
	}
	else {
		this->line[0].color = sf::Color(255, 255, 180, 30);
		this->line[1].color = sf::Color(255, 255, 180, 30);
	}
	window.draw(this->line);
}

