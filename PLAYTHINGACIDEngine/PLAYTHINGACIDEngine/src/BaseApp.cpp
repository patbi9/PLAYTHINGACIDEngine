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

	// Create a square shape
	m_squarePtr = EngineUtilities::MakeShared<CShape>();
	if (m_squarePtr)
	{
		m_squarePtr->createShape(ShapeType::RECTANGLE);
		m_squarePtr->setFillColor(sf::Color::White);
		m_squarePtr->setPosition(400.f, 150.f); // posición al lado del círculo
	}

	// Create a triangle shape
	m_trianglePtr = EngineUtilities::MakeShared<CShape>();
	if (m_trianglePtr)
	{
		m_trianglePtr->createShape(ShapeType::TRIANGLE);
		m_trianglePtr->setFillColor(sf::Color::White);
		m_trianglePtr->setPosition(600.f, 150.f); // posicion al lado del cuadrado
	}

	return true;
}

void
BaseApp::update() {
}

void
BaseApp::render() {
	m_windowPtr->clear();
	if (m_shapePtr) {
		m_shapePtr->render(m_windowPtr); // Asumiendo que render es un método de sf::Shape
		// draw toma un sf::Shape&, así que desreferenciamos
		//m_windowPtr->draw(*m_shapePtr);
	}

	if (m_squarePtr) {
		m_squarePtr->render(m_windowPtr); // Asumiendo que render es un método de sf::Shape
		// draw toma un sf::Shape&, así que desreferenciamos
		//m_windowPtr->draw(*m_shapePtr);
	}

	if (m_trianglePtr) {
		m_trianglePtr->render(m_windowPtr); // Asumiendo que render es un método de sf::Shape
		// draw toma un sf::Shape&, así que desreferenciamos
		//m_windowPtr->draw(*m_shapePtr);
	}

	m_windowPtr->display();
}

void
BaseApp::destroy() {
	m_shapePtr.reset();
	//m_window->destroy();
}