#include "BaseApp.h"
#include "Math/EngineMath.h"


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
  m_windowPtr->handleEvents();
  update();
  render();
 }

 destroy();
 return 0;
}

bool
BaseApp::init() {
 m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "PLAYTHINGACIDEngine");
 if (!m_windowPtr) {
  ERROR("BaseApp",
		"init",
		"Failed to create window pointer, check memory allocation");
  return false;
 }

 //create circle actor
 m_ACircle = EngineUtilities::MakeShared<Actor>("Square Actor");
 if (m_ACircle) {
  m_ACircle->getComponent<CShape>()->createShape(ShapeType::RECTANGLE);
  m_ACircle->getComponent<CShape>()->setFillColor(sf::Color::Red);
  m_ACircle->getComponent<Transform>()->setPosition(sf::Vector2f(300.f, 150.f));
  m_ACircle->getComponent<Transform>()->setRotation(sf::Vector2f(45.f, 45.f));
  //m_ACircle->setName("Circle Actor");
 }
 else {
  ERROR("BaseApp",
		"init",
		"Failed to create circle actor, check memory allocation");
  return false;
 }
 
 //los waypoints (no me gusta vivir)
 m_waypoints.push_back(sf::Vector2f(1200.f, 100.f));
 m_waypoints.push_back(sf::Vector2f(1200.f, 600.f));
 m_waypoints.push_back(sf::Vector2f(300.f, 600.f));
 m_waypoints.push_back(sf::Vector2f(300.f, 150.f)); // regreso al inicio, opcional

 return true;
}

void BaseApp::update() {
    if (!m_windowPtr.isNull()) {
        m_windowPtr->update();
    }

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

 if (!m_ACircle.isNull()) {
  m_ACircle->getComponent<CShape>()->render(m_windowPtr);
 }

 m_windowPtr->display();
}

void
BaseApp::destroy() {
 //m_window->destroy();
}