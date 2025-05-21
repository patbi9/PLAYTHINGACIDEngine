#pragma once
#include "Prerequisites.h"
#include "Window.h"

class
	BaseApp
{
public:
	BaseApp() = default;
	~BaseApp();

	//ejecutar aplicacion en main
	int
	run();

	//inicializacion
	bool
	init();

	//actualización por frame
	void
	update();

	//renderizado
	void
	render();

	void
	destroy();

private:

	Window* m_window;
	//sf::RenderWindow* m_window;
	sf::CircleShape* m_circle;
	sf::RectangleShape* m_square;

};