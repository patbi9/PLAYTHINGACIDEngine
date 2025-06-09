#pragma once
#include "Prerequisites.h"
#include "Window.h"

/**
 * @class BaseApp
 * @brief La estructura principal del engine. Contiene la ejecuci�n, inicializaci�n, actualizaci�n, renderizado, y destruccion.
 *
 */
class BaseApp {
public:
 /**
  * @brief Constructor
  */
 BaseApp() = default;

 /**
 * @brief Destructor
 */
 ~BaseApp();

 /**
  * @brief Ejecuta el coreloop
  *
  */
 int run();

 /**
  * @brief Inicializa la ventana y los gr�ficos
  */
 bool init();

 /**
  * @brief Actualiza cada frame
  */
 void update();

 /**
  * @brief Renderiza los elementos por cada frame
  */
 void render();

 /**
  * @brief Destruye la ventana
  */
 void destroy();

private:
 Window* m_window;             /**< Puntero a la clase Window */
 sf::CircleShape* m_circle;    /**< Puntero a un c�rculo */
 sf::RectangleShape* m_square; /**< Puntero a un rect�ngulo */
};
