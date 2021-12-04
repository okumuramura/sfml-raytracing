#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include "Ray.h"

#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include "Particles.h"
#include "Ray.h"

sf::Vector2f vectorNormalize(sf::Vector2f v) {
	float len = std::sqrtf(v.x * v.x + v.y * v.y);
	return sf::Vector2f(v.x / len, v.y / len);
}

void RayTrace();

int main() {
	RayTrace();
	return 0;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Ray Tracing", sf::Style::Default, settings);

	sf::Event e;
	std::vector<sf::VertexArray> objects;
	sf::Color Gray = sf::Color(80, 80, 80);
	sf::Vector2f mouse_pos, idle_mouse(-1.f, -1.f);

	sf::VertexArray square(sf::Quads, 4);
	square[0].position = sf::Vector2f(100.f, 100.f);
	square[1].position = sf::Vector2f(200.f, 100.f);
	square[2].position = sf::Vector2f(200.f, 200.f);
	square[3].position = sf::Vector2f(100.f, 200.f);
	objects.push_back(square);

	sf::VertexArray triangle(sf::Triangles, 3);
	triangle[0].position = sf::Vector2f(400.f, 400.f);
	triangle[1].position = sf::Vector2f(300.f, 300.f);
	triangle[2].position = sf::Vector2f(500.f, 300.f);
	objects.push_back(triangle);

	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(700.f, 200.f);
	line[1].position = sf::Vector2f(500.f, 500.f);
	objects.push_back(line);
	
	Ray ray;
	Ray::Colide colide;
	sf::Text dis;
	sf::Font dis_font;
	dis_font.loadFromFile("arial.ttf");
	dis.setFont(dis_font);
	dis.setCharacterSize(10);
	sf::Vector2f origin(400.f, 200.f);
	ray.move(origin);
	while (window.isOpen()) {
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) window.close();
		}
		mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
		if (mouse_pos == idle_mouse) continue;
		window.clear();
		idle_mouse = mouse_pos;
		ray.rotate(vectorNormalize(mouse_pos - origin));
		for (int i = 0; i < objects.size(); i++) {
			window.draw(objects[i]);
		}
		colide = ray.cast_closest(objects);
		if (colide.isCollide)
			dis.setString(std::to_string(colide.distance));
		else
			dis.setString("");
		dis.setPosition(origin.x, origin.y - 20);
		window.draw(dis);
		ray.draw(window);
		window.display();
	}
}

void RayTrace(){
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Ray Tracing", sf::Style::Default, settings);

	sf::Event e;
	std::vector<sf::VertexArray> objects;
	sf::Color Gray = sf::Color(80, 80, 80);
	sf::Vector2f mouse_pos, idle_mouse(-1.f, -1.f);

	sf::VertexArray square(sf::Quads, 4);
	square[0].position = sf::Vector2f(100.f, 100.f);
	square[1].position = sf::Vector2f(200.f, 100.f);
	square[2].position = sf::Vector2f(200.f, 200.f);
	square[3].position = sf::Vector2f(100.f, 200.f);
	objects.push_back(square);

	sf::VertexArray triangle(sf::Triangles, 3);
	triangle[0].position = sf::Vector2f(400.f, 400.f);
	triangle[1].position = sf::Vector2f(300.f, 300.f);
	triangle[2].position = sf::Vector2f(500.f, 300.f);
	objects.push_back(triangle);

	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(700.f, 200.f);
	line[1].position = sf::Vector2f(500.f, 500.f);
	objects.push_back(line);

	//Ray ray(sf::Vector2f(-1.f, 0.f));

	Particles particles(100, 100, 3000);

	while (window.isOpen()) {
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) window.close();
		}
		mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
		if (mouse_pos == idle_mouse) continue;
		window.clear();
		idle_mouse = mouse_pos;
		//ray.move(mouse_pos);
		particles.move(mouse_pos);
		for (int i = 0; i < objects.size(); i++) {
			//ray.cast(objects[i]);
			window.draw(objects[i]);
		}
		particles.cast_to_all(objects);
		//ray.draw(window);
		particles.draw(window);
		window.display();
	}
}

