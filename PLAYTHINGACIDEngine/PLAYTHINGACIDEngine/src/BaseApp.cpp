#include "BaseApp.h"
#include "Math/EngineMath.h"
#include "ECS/Texture.h"
#include "ResourceManager.h"
#include <imgui.h>


BaseApp::~BaseApp() {
}

int
BaseApp::run() {
 if (!init()) {
  ERROR("BaseApp",
	    "run",
		"Initializes result on a false statement, check method validations");
 }

 while (m_windowPtr->isOpen()) {
  m_windowPtr->handleEvents(m_engineGUI);
  update();
  render();
 }

 destroy();
 return 0;
}

bool
BaseApp::init() {

	ResourceManager& resourceMan = ResourceManager::getInstance();

 m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "PLAYTHINGACIDEngine");
 if (!m_windowPtr) {
  ERROR("BaseApp",
		"init",
		"Failed to create window pointer, check memory allocation");
  return false;
 }

 //initialize imgui resource
 m_engineGUI.init(m_windowPtr);

 //create circle actor
 m_ACircle = EngineUtilities::MakeShared<Actor>("Square Actor");
 if (m_ACircle) {
  m_ACircle->getComponent<CShape>()->createShape(ShapeType::RECTANGLE);
  m_ACircle->getComponent<CShape>()->setFillColor(sf::Color::White);
  m_ACircle->getComponent<Transform>()->setPosition(sf::Vector2f(479.f, 350.f));
  m_ACircle->getComponent<Transform>()->setScale(sf::Vector2f(.86f, .75f));
  //m_ACircle->getComponent<Transform>()->setRotation(sf::Vector2f(45.f, 45.f));

  //cargar la textura del actor
  if (!resourceMan.loadTexture("Sprites/BlueRegrowFortifiedCamo", "png")) {
	  ERROR("BaseApp", "Init", "Can´t load texture, check file path or extension");
  }
  m_ACircle->setTexture(resourceMan.getTexture("Sprites/BlueRegrowFortifiedCamo"));
  //m_ACircle->setName("Circle Actor");
 }
 else {
  ERROR("BaseApp",
		"init",
		"Failed to create circle actor, check memory allocation");
  return false;
 }

 //create track actor
 m_ATrack = EngineUtilities::MakeShared<Actor>("Track Actor");
 if (m_ATrack) {
     m_ATrack->getComponent<CShape>()->createShape(ShapeType::RECTANGLE);
     m_ATrack->getComponent<CShape>()->setFillColor(sf::Color::White);
     m_ATrack->getComponent<Transform>()->setPosition(sf::Vector2f(0.f, 0.f));
     m_ATrack->getComponent<Transform>()->setScale(sf::Vector2f(15.f, 9.69f));
     //m_ACircle->getComponent<Transform>()->setRotation(sf::Vector2f(45.f, 45.f));

     //cargar la textura del actor
     if (!resourceMan.loadTexture("Sprites/SpaPits", "png")) {
         ERROR("BaseApp", "Init", "Can´t load texture, check file path or extension");
     }
     m_ATrack->setTexture(resourceMan.getTexture("Sprites/SpaPits"));
     //m_ACircle->setName("Circle Actor");
 }
 else {
     ERROR("BaseApp",
         "init",
         "Failed to create track actor, check memory allocation");
     return false;
 }


 
 //los waypoints (no me gusta vivir)
 m_waypoints.push_back(sf::Vector2f(479.f, 350.f));
 m_waypoints.push_back(sf::Vector2f(650.f, 408.f));
 m_waypoints.push_back(sf::Vector2f(814.f, 563.f));
 m_waypoints.push_back(sf::Vector2f(981.f, 641.f));
 m_waypoints.push_back(sf::Vector2f(1138.f, 571.f));
 m_waypoints.push_back(sf::Vector2f(1204.f, 408.f));
 m_waypoints.push_back(sf::Vector2f(1137.f, 271.f));
 m_waypoints.push_back(sf::Vector2f(974.f, 188.f));
 m_waypoints.push_back(sf::Vector2f(820.f, 238.f));
 m_waypoints.push_back(sf::Vector2f(724.f, 378.f));
 m_waypoints.push_back(sf::Vector2f(729.f, 551.f));
 m_waypoints.push_back(sf::Vector2f(660.f, 715.f));
 m_waypoints.push_back(sf::Vector2f(491.f, 792.f));
 m_waypoints.push_back(sf::Vector2f(322.f, 745.f));
 m_waypoints.push_back(sf::Vector2f(244.f, 585.f));
 m_waypoints.push_back(sf::Vector2f(301.f, 398.f));



 return true;
}

void BaseApp::update() {
    if (!m_windowPtr.isNull()) {
        m_windowPtr->update();
    }

	//update ImGui
	m_engineGUI.update(m_windowPtr, m_windowPtr->deltaTime);

    ImGui::ShowDemoWindow();

    if (!m_ATrack.isNull())
        m_ATrack->update(m_windowPtr->deltaTime.asSeconds());

    if (!m_ACircle.isNull() && !m_waypoints.empty()) {
        m_ACircle->update(m_windowPtr->deltaTime.asSeconds());

        // Posición actual del actor
        sf::Vector2f currentPos = m_ACircle->getComponent<Transform>()->getPosition();

        // Posición del waypoint actual
        sf::Vector2f targetPos = m_waypoints[m_currentWaypointIndex];

        // Calcular distancia
        float distance = EngineMath::distance(
            currentPos.x, currentPos.y,
            targetPos.x, targetPos.y
        );

        // Si está suficientemente cerca, pasar al siguiente waypoint
        if (distance < 10.0f) {
            m_currentWaypointIndex = (m_currentWaypointIndex + 1) % m_waypoints.size();
        }

        // Mover al siguiente waypoint
        targetPos = m_waypoints[m_currentWaypointIndex];
        m_ACircle->getComponent<Transform>()->seek(targetPos, 200.0f, m_windowPtr->deltaTime.asSeconds(), 10.0f);
    }
}


void
BaseApp::render() {
 if (!m_windowPtr) {
  return;
 }

 m_windowPtr->clear();

 if (!m_ATrack.isNull()) {
     m_ATrack->getComponent<CShape>()->render(m_windowPtr);
 }

 if (!m_ACircle.isNull()) {
  m_ACircle->getComponent<CShape>()->render(m_windowPtr);
 }

 m_windowPtr->render();

//render ImGui
 m_engineGUI.render(m_windowPtr);

 m_windowPtr->display();
}

void
BaseApp::destroy() {
	//destroy ImGui resources
	m_engineGUI.destroy();

 //m_window->destroy();
}