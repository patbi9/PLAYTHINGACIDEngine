/**
 * @file EngineGUI.h
 * @brief Immediate-mode GUI layer for the engine: init, update, render, and UI panels (outliner, inspector, console, leaderboard).
 *
 * @details
 * EngineGUI encapsulates GUI setup, per-frame updates, and rendering. It exposes
 * common editor-like widgets such as a menu bar, outliner (actors list), inspector
 * (properties of the selected actor), a console view for program messages, and a
 * leaderboard for racing scenarios. Event processing hooks are provided to feed
 * input from the OS/windowing layer.
 *
 * @note The implementation is expected to rely on the engine's windowing system
 * and SFML types for timing/events.
 */

#pragma once
#include "Prerequisites.h"
#include <vector>

class Window;
class Actor;
class A_Racer;

/**
 * @class EngineGUI
 * @brief GUI manager that owns editor-like panels and handles per-frame UI.
 */
class
 EngineGUI {
 public:
 /**
  * @brief Default constructor.
  */
 EngineGUI() = default;

 /**
  * @brief Default destructor.
  */
 ~EngineGUI() = default;

 /**
  * @brief Initializes GUI resources and connects to the window/context.
  * @param window Shared pointer to the engine window/context.
  *
  * @details
  * Should perform GUI-backend initialization and any required font/style setup.
  */
 void
 init(const EngineUtilities::TSharedPointer<Window>& window);

 /**
  * @brief Advances GUI state for the current frame.
  * @param window Shared pointer to the engine window/context.
  * @param deltaTime Frame time (SFML time span since the last update).
  *
  * @details
  * Build UI for the frame and handle input-driven state changes (selection, edits).
  */
 void
 update(const EngineUtilities::TSharedPointer<Window>& window,
 sf::Time deltaTime);

 /**
  * @brief Renders the GUI draw data to the current window/context.
  * @param window Shared pointer to the engine window/context.
  */
 void
 render(const EngineUtilities::TSharedPointer<Window>& window);

 /**
  * @brief Shuts down the GUI layer and releases resources.
  */
 void
 destroy();

 /**
  * @brief Forwards window events to the GUI system.
  * @param window Reference to the OS window (SFML).
  * @param event  SFML event to process (keyboard/mouse/window).
  *
  * @note Call this from your main event loop to keep GUI input responsive.
  */
 void
 processEvent(const sf::Window& window, const sf::Event& event);

 /**
  * @brief Applies the GUI visual style (colors, rounding, padding).
  * @details
  * Can be called during init or at runtime to switch themes.
  */
 void
 setupGUIStyle();

 /**
  * @brief Draws the application/editor menu bar.
  * @details
  * Typically exposes top-level actions (File, View, Help, etc.).
  */
 void
 barMenu();

 /**
  * @brief Displays a hierarchical/flat list of scene actors (Outliner).
  * @param actors Collection of actors to display/select.
  *
  * @details
  * Selection updates @ref selectedActorIndex to drive the Inspector panel.
  */
 void
 outliner(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

 /**
  * @brief Shows a console panel with categorized program messages.
  * @param programMessages Map from message category to list of log lines.
  *
  * @note The key type `ConsolErrorType` is assumed to enumerate message kinds
  * (e.g., Info/Warning/Error).
  */
 void
 console(const std::map<ConsolErrorType, std::vector<std::string>>& programMessages);

 /**
  * @brief Displays and edits properties of the currently selected actor.
  * @param actors Collection of actors (indexed by @ref selectedActorIndex).
  */
 void
 inspector(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

 /**
  * @brief Draws a 2D vector control with a label and reset functionality.
  * @param label        UI label for the control.
  * @param values       Pointer to two contiguous floats (x, y) to edit.
  * @param resetValues  Default value applied when reset is triggered (per component).
  * @param columnWidth  Label column width in pixels.
  *
  * @warning Expects @p values to reference valid memory for two floats.
  */
 void
 vec2Control(const std::string& label,
 float* values,
 float resetValues = 0.0f,
 float columnWidth = 100.0f);

 /**
  * @brief Renders a leaderboard view for racer actors.
  * @param racers Collection of racers to display/rank.
  *
  * @details
  * Sorting/formatting responsibilities depend on the implementation.
  */
 void
 leaderboard(const std::vector<EngineUtilities::TSharedPointer<A_Racer>>& racers);

 private:
 /** @brief Index of the currently selected actor in @ref outliner; -1 means none. */
 int selectedActorIndex = -1;
};

