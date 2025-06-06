#pragma once
#include "Prerequisites.h"

class Window;

/**
 * @class CShape
 * @brief Encapsula las formas gr�ficas con SFML
 *
 */
class CShape {
public:
    /**
     * @brief Constructor
     */
    CShape() = default;

    /**
     * @brief Constructor. Recibe el tipo de forma.
     * @param shapeType Tipo de forma que va a crear
     */
    CShape(ShapeType shapeType);

    /**
     * @brief Destructor por defecto
     */
    ~CShape() = default;

    /**
     * @brief Crea una forma seg�n el ShapeType espec�ficado
     * @param shapeType Tipo de forma que va a crear
     * @return Puntero a la forma creada
     */
    sf::Shape* createShape(ShapeType shapeType);

    /**
     * @brief Update de la l�gica interna de la forma
     * @param deltaTime Tiempo que pas� desde la �ltima update
     */
    void update(float deltaTime);

    /**
     * @brief Renderiza la forma en la ventana
     * @param window Referencia a la ventana donde se va a dibujar
     */
    void render(Window& window);

    /**
     * @brief Establece la posici�n de la forma
     * @param x Posici�n en X
     * @param y Posici�n en Y
     */
    void setPosition(float x, float y);

    /**
     * @brief Establece la posici�n de la forma
     * @param position Vector con X, Y
     */
    void setPosition(const sf::Vector2f& position);

    /**
     * @brief Establece el color de la figura
     * @param color El color
     */
    void setFillColor(const sf::Color& color);

    /**
     * @brief Rotaci�n de la forma
     * @param angle �ngulo por el que se va a rotar
     */
    void setRotation(float angle);

    /**
     * @brief Tama�o de la forma
     * @param scl Vector con el factor de escala en X y Y.
     */
    void setScale(const sf::Vector2f& scl);

    /**
     * @brief Obtiene la forma SFML oculta
     * @return Puntero a la forma
     */
    sf::Shape* getShape();

private:
    sf::Shape* m_shape;              /**< Puntero a la forma actual */
    ShapeType m_shapeType;           /**< Tipo de forma */
    sf::VertexArray* m_line;         /**< Auxiliar para debug. */
};