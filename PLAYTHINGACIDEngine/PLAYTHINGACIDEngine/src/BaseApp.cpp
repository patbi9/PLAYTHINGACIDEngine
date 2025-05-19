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
        handleEvents();
        update();
        render();
    }

    destroy();
    return 0;
}

bool BaseApp::init()
{
    m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "PLAYTHINGACIDEngine");

    m_circle = new sf::CircleShape(100.0f);
    m_circle->setFillColor(sf::Color::White);
    m_circle->setPosition(200.f, 150.f);

    m_square = new sf::RectangleShape(sf::Vector2f(190.f, 190.f));
    m_square->setFillColor(sf::Color::White);
    m_square->setPosition(400.f, 150.f);
	return true;
}

void BaseApp::update()
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
    delete m_window;
    delete m_circle;
    delete m_square;
}

void BaseApp::handleEvents()
{
    sf::Event event;
    while (m_window->pollEvent(event)) {
        // Cerrar la ventana si el usuario lo indica
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }
    }
}

