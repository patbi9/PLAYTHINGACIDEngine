#include "CShape.h"
#include "Window.h"

void
CShape::createShape(ShapeType type) {
    m_shapeType = type;
    switch (type) {
    case ShapeType::CIRCLE: {
        auto circleSP = EngineUtilities::MakeShared<sf::CircleShape>(100.f);
        circleSP->setFillColor(sf::Color::White);
        m_shapePtr = circleSP.dynamic_pointer_cast<sf::Shape>();
        break;
    }
    case ShapeType::RECTANGLE: {
        auto rectSP = EngineUtilities::MakeShared<sf::RectangleShape>(sf::Vector2f(200.f, 200.f));
        rectSP->setFillColor(sf::Color::White);
        m_shapePtr = rectSP.dynamic_pointer_cast<sf::Shape>();
        break;
    }
    case ShapeType::TRIANGLE: {
        auto triSP = EngineUtilities::MakeShared<sf::ConvexShape>(3);
        triSP->setPoint(0, { 0,0 });
        triSP->setPoint(1, { 100,200 });
        triSP->setPoint(2, { 200,0 });
        triSP->setFillColor(sf::Color::White);
        m_shapePtr = triSP.dynamic_pointer_cast<sf::Shape>();
        break;
    }
    case ShapeType::POLYGON: {
        auto polySP = EngineUtilities::MakeShared<sf::ConvexShape>(5);
        polySP->setPoint(0, { 0,0 });
        polySP->setPoint(1, { 50,100 });
        polySP->setPoint(2, { 100,0 });
        polySP->setPoint(3, { 75,-50 });
        polySP->setPoint(4, { -25,-50 });
        polySP->setFillColor(sf::Color::White);
        m_shapePtr = polySP.dynamic_pointer_cast<sf::Shape>();
        break;
    }
    default:
        m_shapePtr.reset();
        ERROR("CShape", "createShape", "Tipo desconocido");
        return;
    }
}

void
CShape::render(const EngineUtilities::TSharedPointer<Window>& window) {
    if (m_shapePtr) {
        window->draw(*m_shapePtr);
    }
}

void CShape::setPosition(float x, float y) {
    if (m_shapePtr) m_shapePtr->setPosition(x, y);
    else ERROR("CShape", "setPosition", "Shape no inicializado");
}

void CShape::setFillColor(const sf::Color& color) {
    if (m_shapePtr) m_shapePtr->setFillColor(color);
    else ERROR("CShape", "setFillColor", "Shape no inicializado");
}

void CShape::setRotation(float angle) {
    if (m_shapePtr) m_shapePtr->setRotation(angle);
    else ERROR("CShape", "setRotation", "Shape no inicializado");
}

void CShape::setScale(const sf::Vector2f& scale) {
    if (m_shapePtr) m_shapePtr->setScale(scale);
    else ERROR("CShape", "setScale", "Shape no inicializado");
}