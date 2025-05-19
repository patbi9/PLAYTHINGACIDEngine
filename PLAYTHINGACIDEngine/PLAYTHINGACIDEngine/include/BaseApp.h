#pragma once
#include "Prerequisites.h"

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

	void
	handleEvents();

private:
	sf::RenderWindow* m_window;
	sf::CircleShape* m_circle;
	sf::RectangleShape* m_square;

};