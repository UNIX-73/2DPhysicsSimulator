#include "graphicWindow.h"
#include <iostream>

GraphicWindow::GraphicWindow(int width, int height) :
	WINDOW_WIDTH(width), WINDOW_HEIGHT(height), event(sf::Event())
{
    window.create(sf::VideoMode(width, height), "Car Physics Simulator 2");


    cameraPos = V2(-width / 2.0, height / 2.0);
    windowCenter = cameraPos;
}

void GraphicWindow::UpdateWindow()
{
	ManageWindowEvents();
}

void GraphicWindow::UpdateGraphics(sf::Color backgroundColor)
{
	if (window.isOpen())
	{
        SetCameraPos(cameraPos + addCameraOffset);
        SetZoom(zoom + zoomOffset);
        addCameraOffset = V2::ZeroVector;
        zoomOffset = 0.0;

		window.clear(backgroundColor);

        windowCenter = V2(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
		
        for (std::shared_ptr<GraphicObject> obj : graphicObjects)
        {
            DrawGraphicObject(obj);
        }

		window.display();
	}
	else
	{

	}
}

void GraphicWindow::SetCameraPos(V2 newCameraPos)
{
    this->cameraPos = newCameraPos;
}

void GraphicWindow::SetZoom(double newZoom)
{
    this->zoom = newZoom;
}

void GraphicWindow::MoveCamera(const V2& addCameraOffset, double step)
{
    this->addCameraOffset += V2(addCameraOffset.x, -addCameraOffset.y) * cameraSpeed * step; //se invierte la y
}

void GraphicWindow::ChangeZoom(double zoom, double step)
{
    this->zoomOffset += zoom * zoomSpeed * step;
}

void GraphicWindow::AddGraphicObject(std::shared_ptr<GraphicObject>& obj)
{
    graphicObjects.push_back(obj);
}

void GraphicWindow::AddGraphicObjects(std::vector<std::shared_ptr<GraphicObject>>& objects)
{
    for (auto obj : objects)
    {
        graphicObjects.push_back(obj);
    }
}

void GraphicWindow::RemoveGraphicObject(std::shared_ptr<GraphicObject>& obj)
{
    auto it = std::find(graphicObjects.begin(), graphicObjects.end(), obj);
    if (it != graphicObjects.end())
    {
        graphicObjects.erase(it);
    }
}

void GraphicWindow::RemoveGraphicObjects(std::vector<std::shared_ptr<GraphicObject>>& objects)
{
    for (auto obj : objects)
    {
        auto it = std::find(graphicObjects.begin(), graphicObjects.end(), obj);
        if (it != graphicObjects.end())
        {
            graphicObjects.erase(it);
        }
    }
}


void GraphicWindow::ManageWindowEvents() {
    while (window.pollEvent(event)) { //No es un bucle infinito ya que al coger los eventos faltantes devuelve false
       
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::Resized:
            WINDOW_WIDTH = event.size.width;
            WINDOW_HEIGHT = event.size.height;
            break;

        default:
            break;
        }
    }
}

void GraphicWindow::DrawGraphicObject(std::shared_ptr<GraphicObject> obj)
{
    V2 wPos = obj->wPos;
    double wRotation = obj->wRotation;

    for (sf::RectangleShape& shape : obj->rectangleShapes)
    {
        V2 rPos(shape.getPosition().x, shape.getPosition().y);
        float rRotation = shape.getRotation();

        // Calcular la rotación global de la forma
        float shapeWRotation = rRotation - wRotation;

        // Calcular la posición global de la forma
        V2 diffToObjOrigin = wPos - rPos.rotateVector(wRotation);
        V2 shapeCameraPos = (wPos + diffToObjOrigin - cameraPos) * zoom * 0.5;

        shape.setPosition(sf::Vector2f(shapeCameraPos.x, -shapeCameraPos.y)); //En gráficos el y está invertido
        shape.setRotation(shapeWRotation);

        shape.setScale(zoom, zoom);

        window.draw(shape);

        // Restaurar la posición y rotación originales
        shape.setPosition(sf::Vector2f(rPos.x, rPos.y));
        shape.setRotation(rRotation);
    }
}