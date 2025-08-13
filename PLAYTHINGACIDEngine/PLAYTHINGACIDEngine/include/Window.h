#pragma once
#include "Prerequisites.h"

class EngineGUI;

/**
 * @class Window
 * @brief Clase que encapsula una ventana SFML
 *
 */
class
 Window {
public:
 /**
  * @brief Constructor
  */
 Window() = default;

 /**
  * @brief Constructor que crea una ventana con las dimensiones que se especifican
  * @param width Ancho de la ventana
  * @param height Alto de la ventana
  * @param title Título de la ventana
  */
 Window(int width, int height, const std::string& title);

 /**
  * @brief Destructor
  */
 ~Window();

 /**
  * @brief Maneja los eventos de la ventana
  */
 void
	 handleEvents(EngineGUI& engineGUI);

 /**
  * @brief Verifica si la ventana está abierta
  * @return Booleano si la ventana sigue abierta
  */
 bool
  isOpen() const;

 /**
  * @brief Borra el contenido de la ventana
  * @param color Color de fondo negro
  */
 void
  clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

 /**
  * @brief Dibuja un objeto en la ventana
  * @param drawable Objeto SFML que puede dibujarse
  * @param states Estados de renderizado
  */
 void
  draw(const sf::Drawable& drawable,
  const sf::RenderStates& states = sf::RenderStates::Default);

 /**
  * @brief Muestra lo que se dibujó
  */
 void
  display();

 void
	 update();

 void
	 render();

 /**
  * @brief Destruye la ventana
  */
 void
  destroy();

private:
 sf::View m_view;
public:
	EngineUtilities::TUniquePtr < sf::RenderWindow> m_windowPtr;
 sf::Time deltaTime;
 sf::Clock clock;
};
