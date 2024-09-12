#pragma once
#include <vector>
#include <memory>
#include "V2.h"
#include <SFML\Graphics.hpp>

class GraphicObject
{
public:
	GraphicObject(const sf::RectangleShape shape = sf::RectangleShape()); //se puede añadir una forma única
	GraphicObject(const std::vector<sf::RectangleShape> shapesArray);

	void AddShape(const sf::RectangleShape shape);
	void AddShapes(const std::vector<sf::RectangleShape> shapesArray);

	//Variables globales
	V2 wPos;
	double wRotation = 0.0;
		
	std::vector<sf::RectangleShape> rectangleShapes;
};
