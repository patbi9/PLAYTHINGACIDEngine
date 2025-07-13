#include "BaseApp.h"


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

	// Create a circle shape
	m_shapePtr = EngineUtilities::MakeShared<CShape>();
	if (m_shapePtr)
	{
		m_shapePtr->createShape(ShapeType::CIRCLE);
		m_shapePtr->setFillColor(sf::Color::White);
		m_shapePtr->setPosition(200.f, 150.f);
	}

	//create circle actor
	m_ACircle = EngineUtilities::MakeShared<Actor>("Circle Actor");
	if (m_ACircle) {
		m_ACircle->getComponent<CShape>()->createShape(ShapeType::CIRCLE);
		m_ACircle->getComponent<CShape>()->setFillColor(sf::Color::Green);
		m_ACircle->getComponent<Transform>()->setPosition(sf::Vector2f(500.f, 150.f));
		//m_ACircle->setName("Circle Actor");
	}
	else {
		ERROR("BaseApp",
			"init",
			"Failed to create circle actor, check memory allocation");
		return false;
	}

	return true;

}

void
BaseApp::update() {
	//update actor
	if (!m_ACircle.isNull()) {
		m_ACircle->update(0);
	}
}

void
BaseApp::render() {
	if (!m_windowPtr) {
		return;
	}
	m_windowPtr->clear();
	if (m_shapePtr) {
		m_shapePtr->render(m_windowPtr);
	}
	if (!m_ACircle.isNull()) {
		m_ACircle->getComponent<CShape>()->render(m_windowPtr);
	}
	m_windowPtr->display();
}

void
BaseApp::destroy() {
	m_shapePtr.reset();
	//m_window->destroy();
}