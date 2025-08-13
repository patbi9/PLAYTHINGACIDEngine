#pragma once
#include "Prerequisites.h"

class EngineGUI;

/**
 * @class Window
 * @brief Class that encapsulates SFML window
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
  * @brief Constructor that creates a window with specified dimensions
  * @param width
  * @param height
  * @param title
  */
 Window(int width, int height, const std::string& title);

 /**
  * @brief Destructor
  */
 ~Window();

 /**
  * @brief Manages window events
  */
 void
	 handleEvents(EngineGUI& engineGUI);

 /**
  * @brief Verifies if window is open
  * @return Bool is window open
  */
 bool
  isOpen() const;

 /**
  * @brief Deletes window content
  * @param color Black background
  */
 void
  clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

 /**
  * @brief Draws an object on window
  * @param drawable SFML object
  * @param states Render states
  */
 void
  draw(const sf::Drawable& drawable,
  const sf::RenderStates& states = sf::RenderStates::Default);

 /**
  * @brief Shows what was drawn
  */
 void
  display();

 /**
 * @brief Window's update
 */
 void
	 update();

 /**
  * @brief Window's render
  */
 void
	 render();

 /**
  * @brief Destroys window
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
