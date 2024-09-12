#pragma once
#include "graphicObject.h"

class GraphicWindow
{
public:
	sf::RenderWindow window;

	GraphicWindow(int width, int height);
	~GraphicWindow() = default;

	void UpdateWindow(); //La idea es que refresque la ventana y sus funcionalidades, se actualiza en el while principal

	void UpdateGraphics(sf::Color backgroundColor); //No tiene por que ser llamado cada bucle del while principal, ya que como las físicas irán a unos 2k hz se puede llamar cada x bucle de físicas

	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;

	double cameraSpeed = 600.0;
	double zoomSpeed = 5.0;

	V2 cameraPos;
	double zoom = 1.0;

	void SetCameraPos(V2 newCameraPos);
	void SetZoom(double newZoom);
	void MoveCamera(const V2& addCameraOffset, double step);
	void ChangeZoom(double zoom, double step);

	//Graphic objects
	void AddGraphicObject(std::shared_ptr<GraphicObject>& obj);
	void AddGraphicObjects(std::vector<std::shared_ptr<GraphicObject>>& objects);

	void RemoveGraphicObject(std::shared_ptr<GraphicObject>& obj);
	void RemoveGraphicObjects(std::vector<std::shared_ptr<GraphicObject>>& objects);


protected:
	sf::Event event;

	std::vector<std::shared_ptr<GraphicObject>> graphicObjects;

	V2 addCameraOffset;
	double zoomOffset = 0.0;

	V2 windowCenter;

	void ManageWindowEvents();

	void DrawGraphicObject(std::shared_ptr<GraphicObject> obj); //Dibuja un objeto en pantalla
};