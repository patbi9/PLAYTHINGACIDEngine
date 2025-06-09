#pragma once
#include "Prerequisites.h"
#include "Window.h"

/**
 * @class BaseApp
 * @brief La estructura principal del engine. Contiene la ejecución, inicialización, actualización, renderizado, y destruccion.
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
  * @brief Inicializa la ventana y los gráficos
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
 sf::CircleShape* m_circle;    /**< Puntero a un círculo */
 sf::RectangleShape* m_square; /**< Puntero a un rectángulo */
};
