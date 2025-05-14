#include <SFML/Graphics.hpp>

sf::RenderWindow* window;
sf::CircleShape* circle;
sf::RectangleShape* square;

void
init() {
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "PLAYTHINGACIDEngine");

    circle = new sf::CircleShape(100.0f);
    circle->setFillColor(sf::Color::White);
    circle->setPosition(400.f, 150.f);

    square = new sf::RectangleShape(sf::Vector2f(190.f, 190.f));
    square->setFillColor(sf::Color::White);
    square->setPosition(200.f, 150.f);
}

void
handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        // Cerrar la ventana si el usuario lo indica
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }
}

void
update() {

}

void
render() {
    // Limpiar, dibujar y mostrar
    window->clear();
    window->draw(*square);
    window->draw(*circle);
    window->display();
}

void
destroy() {

}

//esto es el gameloop
int
main() {
    init();

    while (window->isOpen()) {
        handleEvents();
        update();
        render();
    }

    destroy();
    return 0;
}