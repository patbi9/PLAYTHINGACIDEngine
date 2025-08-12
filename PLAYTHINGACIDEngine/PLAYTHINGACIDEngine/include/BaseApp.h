#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "CShape.h"
#include "Actor.h"

/**
 * @class BaseApp
 * @brief Main application class that manages the window, initialization, update, rendering, and cleanup.
 *
 * This class is responsible for driving the lifecycle of the engine application,
 * including managing the main loop and handling scene objects like shapes and actors.
 */
class
 BaseApp {
public:
 /**
  * @brief Default constructor.
  */
 BaseApp() = default;

 /**
  * @brief Destructor. Calls destroy internally to clean up resources.
  */
 ~BaseApp();

 /**
  * @brief Entry point for running the application.
  * @return Exit code from the application.
  */
 int
  run();

 /**
  * @brief Initializes the application and its subsystems.
  * @return True if initialization was successful, false otherwise.
  */
 bool
  init();

 /**
  * @brief Updates application logic once per frame.
  */
 void 
  update();

 /**
  * @brief Renders the current frame.
  */
 void 
  render();

 /**
  * @brief Cleans up resources and shuts down the application.
  */
 void 
  destroy();

private:
 EngineUtilities::TSharedPointer<Window> m_windowPtr; ///< Pointer to the application window.
 EngineUtilities::TSharedPointer<Actor> m_ACircle;  ///< Pointer to the first actor.
 EngineUtilities::TSharedPointer<Actor> m_ATrack;   ///< Pointer to the track actor.
 std::vector<sf::Vector2f> m_waypoints;
 size_t m_currentWaypointIndex = 0;
};