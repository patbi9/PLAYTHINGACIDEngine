/**
 * @file BaseApp.h
 * @brief Main application class for bootstrapping the engine, managing the main loop, and orchestrating scene objects.
 *
 * @details
 * BaseApp owns the primary window and high-level subsystems, and exposes the typical
 * application lifecycle: @ref init, @ref update, @ref render, and @ref destroy.
 * It also holds scene entities such as generic @ref Actor instances and specialized
 * @ref A_Racer actors, as well as a waypoint set used by the racing example.
 *
 * @note The implementation is expected to create the window, initialize resources,
 * run the game loop inside @ref run, and clean up in @ref destroy.
 */

#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "CShape.h"
#include "Actor.h"
#include "EngineGUI.H"
#include "A_Racer.h"

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
 *
 * @details
 * Typically performs initialization, enters the main loop (calling @ref update and
 * @ref render once per frame), and finalizes resources at shutdown.
 */
 int
  run();

 /**
 * @brief Initializes the application and its subsystems.
 * @return True if initialization was successful, false otherwise.
 *
 * @details
 * Expected to create the window, initialize graphics/input subsystems, and set up
 * initial scene content (actors, waypoints, GUI).
 */
 bool
  init();

 /**
 * @brief Updates application logic once per frame.
 *
 * @details
 * Advances simulation state (actors, racers, GUI, etc.). The time step handling
 * (fixed vs. variable) depends on the implementation in the .cpp file.
 */
 void
  update();

 /**
 * @brief Renders the current frame.
 *
 * @details
 * Submits draw calls for scene objects and GUI elements to the active window/context.
 */
 void
  render();

 /**
  * @brief Cleans up resources and shuts down the application.
  *
  * @details
  * Releases owned resources (window, actors, GUI data) and prepares for termination.
  */
 void
  destroy();

private:
 /** @brief Generic scene actors owned by the application. */
 std::vector<EngineUtilities::TSharedPointer<Actor>>  m_actors;
 /** @brief Racer-specific actors used in the racing scenario. */
 std::vector<EngineUtilities::TSharedPointer<A_Racer>> m_racers;

 /** @brief Primary application window. */
 EngineUtilities::TSharedPointer<Window> m_windowPtr;
 /** @brief Track actor or container representing the race track/level geometry. */
 EngineUtilities::TSharedPointer<Actor> m_ATrack;

 /** @brief Ordered list of 2D waypoints describing a closed loop for racers. */
 std::vector<sf::Vector2f> m_waypoints;
 /** @brief Current waypoint index for any global/path-related iteration. */
 size_t m_currentWaypointIndex = 0;

 /** @brief Immediate-mode engine GUI wrapper for runtime overlays/controls. */
 EngineGUI m_engineGUI;
};
