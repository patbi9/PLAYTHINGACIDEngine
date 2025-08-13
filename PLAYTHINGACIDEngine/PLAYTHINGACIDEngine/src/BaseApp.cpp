#include "BaseApp.h"
#include "Math/EngineMath.h"
#include "ECS/Texture.h"
#include "ResourceManager.h"
#include "A_Racer.h"
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

 //corredor uno
 auto r1 = EngineUtilities::MakeShared<A_Racer>("CPU_1");
 r1->getComponent<CShape>()->createShape(ShapeType::RECTANGLE);
 r1->getComponent<CShape>()->setFillColor(sf::Color::White);
 r1->getComponent<Transform>()->setScale(sf::Vector2f(.86f, .75f));
 if (!resourceMan.loadTexture("Sprites/BlueRegrowFortifiedCamo", "png")) { /* ... */ }
 r1->setTexture(resourceMan.getTexture("Sprites/BlueRegrowFortifiedCamo"));

 m_racers.push_back(r1);         // <-- necesitas declarar m_racers en BaseApp.h
 m_actors.push_back(r1);

  //corredor dos
 auto r2 = EngineUtilities::MakeShared<A_Racer>("CPU_2");
 r2->getComponent<CShape>()->createShape(ShapeType::RECTANGLE);
 r2->getComponent<CShape>()->setFillColor(sf::Color::White);
 r2->getComponent<Transform>()->setScale(sf::Vector2f(.4f, .55f));
 r2->getComponent<Transform>()->setPosition(sf::Vector2f(1000.f, 100.f));
 if (!resourceMan.loadTexture("Sprites/WhiteCamo", "png")) { /* ... */ }
 r2->setTexture(resourceMan.getTexture("Sprites/WhiteCamo"));

 m_racers.push_back(r2);         // <-- necesitas declarar m_racers en BaseApp.h
 m_actors.push_back(r2);

 //corredor tres
 auto r3 = EngineUtilities::MakeShared<A_Racer>("CPU_3");
 r3->getComponent<CShape>()->createShape(ShapeType::RECTANGLE);
 r3->getComponent<CShape>()->setFillColor(sf::Color::White);
 r3->getComponent<Transform>()->setScale(sf::Vector2f(.6f, .75f));
 if (!resourceMan.loadTexture("Sprites/DreadRockBloonEliteDS3", "png")) { /* ... */ }
 r3->setTexture(resourceMan.getTexture("Sprites/DreadRockBloonEliteDS3"));

 m_racers.push_back(r3);         // <-- necesitas declarar m_racers en BaseApp.h
 m_actors.push_back(r3);

 for (auto& r : m_racers) r->setWaypoints(m_waypoints);

 // parrilla 2x2 de ejemplo
 float rowGap = 100.f;   // distancia hacia atrás entre filas
 float laneGap = 40.f;  // separación lateral entre carriles

 // r1: fila 0 carril -1
 m_racers[0]->spawnRelative(0, 0.f, -laneGap);
 // r2: fila 0 carril +1
 if (m_racers.size() > 1) m_racers[1]->spawnRelative(0, 0.f, +laneGap);
 // r3: fila 1 carril -1
 if (m_racers.size() > 2) m_racers[2]->spawnRelative(0, rowGap, -laneGap);
 // r4: fila 1 carril +1
 if (m_racers.size() > 3) m_racers[3]->spawnRelative(0, rowGap, +laneGap);

 return true;
}

void BaseApp::update() {
    if (!m_windowPtr.isNull()) {
        m_windowPtr->update();
    }

	//update ImGui
	m_engineGUI.update(m_windowPtr, m_windowPtr->deltaTime);
	m_engineGUI.outliner(m_actors);
    m_engineGUI.inspector(m_actors);
    m_engineGUI.leaderboard(m_racers);

    ImGui::ShowDemoWindow();

    if (!m_ATrack.isNull())
        m_ATrack->update(m_windowPtr->deltaTime.asSeconds());

    const float dt = m_windowPtr->deltaTime.asSeconds();
    for (auto& r : m_racers)
        r->update(dt);

   // leaderboard
   struct Node { float prog; EngineUtilities::TSharedPointer<A_Racer> r; };
   std::vector<Node> nodes; nodes.reserve(m_racers.size());
   for (auto& r : m_racers) nodes.push_back({ r->getProgressMeters(), r });
    std::sort(nodes.begin(), nodes.end(), [](auto& a, auto& b){ return a.prog > b.prog; });
     for (int i=0;i<(int)nodes.size();++i) nodes[i].r->setPlace(i+1);
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

 for (auto& r : m_racers)
     r->getComponent<CShape>()->render(m_windowPtr);

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