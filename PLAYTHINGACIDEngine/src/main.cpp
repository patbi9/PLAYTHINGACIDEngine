#include <SFML/Graphics.hpp>

int main()
{
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ejemplo simple de SFML");

    // Crear un cuadrade
    sf::RectangleShape square(sf::Vector2f(190.f, 190.f)); // ancho y alto
    square.setFillColor(sf::Color::White);
    square.setPosition(200.f, 150.f);

    // Crear un círculo
    sf::CircleShape circle(100.f); // radio 100
    circle.setFillColor(sf::Color::White);
    circle.setPosition(400.f, 150.f);

    // Bucle principal
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Cerrar la ventana si el usuario lo indica
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Limpiar, dibujar y mostrar
        window.clear();
        window.draw(square);
        window.draw(circle);
        window.display();
    }

    return 0;
}