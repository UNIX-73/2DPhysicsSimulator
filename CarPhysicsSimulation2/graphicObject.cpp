#include "graphicObject.h"

GraphicObject::GraphicObject(const sf::RectangleShape shape)
{
	rectangleShapes.push_back(shape);
}

GraphicObject::GraphicObject(const std::vector<sf::RectangleShape> shapesArray)
{
	for (sf::RectangleShape shape : shapesArray)
	{
		rectangleShapes.push_back(shape);
	}
}

void GraphicObject::AddShape(const sf::RectangleShape shape)
{
	rectangleShapes.push_back(shape);
}

void GraphicObject::AddShapes(const std::vector<sf::RectangleShape> shapesArray)
{
	for (sf::RectangleShape shape : shapesArray)
	{
		rectangleShapes.push_back(shape);
	}
}
