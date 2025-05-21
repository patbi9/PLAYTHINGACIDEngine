#include "BaseApp.h"

BaseApp::~BaseApp()
{
}

int BaseApp::run()
{
    if (!init()) {
        ERROR("BaseApp", 
              "run", 
              "Initializes result on a false statement, check method validations");
    }

    while (m_window->isOpen()) {
        m_window->handleEvents();
        update();
        render();
    }

    destroy();
    return 0;
}

bool 
BaseApp::init()
{
    m_window = new Window(1920, 1080, "PLAYTHINGACIDEngine");

    m_circle = new sf::CircleShape(100.0f);
    m_circle->setFillColor(sf::Color::White);
    m_circle->setPosition(200.f, 150.f);

    m_square = new sf::RectangleShape(sf::Vector2f(190.f, 190.f));
    m_square->setFillColor(sf::Color::White);
    m_square->setPosition(400.f, 150.f);

	return true;
}

void 
BaseApp::update()
{
}

void BaseApp::render()
{
    // Limpiar, dibujar y mostrar
    m_window->clear();
    m_window->draw(*m_square);
    m_window->draw(*m_circle);
    m_window->display();
}

void BaseApp::destroy()
{
    delete m_circle;
    delete m_square;
    m_window->destroy();
}

