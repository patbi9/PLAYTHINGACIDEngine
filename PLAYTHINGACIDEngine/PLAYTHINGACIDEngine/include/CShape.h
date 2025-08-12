#pragma once
#include "Prerequisites.h"
#include "ECS\Component.h"
#include "ECS\Texture.h"

class Window;
//class Texture;

/**
 * @class CShape
 * @brief Component that represents a drawable shape (circle, rectangle, etc.) within the ECS system.
 *
 * This component handles shape creation, positioning, scaling, rotation, and rendering through SFML.
 */
class
 CShape : public Component {
public:
 /**
  * @brief Default constructor.
  */
 CShape() = default;

/**
 * @brief Constructs a shape component with the specified shape type.
 * @param shapeType Type of shape to initialize.
 */
 CShape(ShapeType shapeType) :
  m_shapePtr(nullptr),
  m_shapeType(ShapeType::EMPTY),
  Component(ComponentType::SHAPE) {
  }

 /**
  * @brief Virtual destructor.
  */
 virtual ~CShape() = default;

 /**
  * @brief Creates an internal shape based on the specified type.
  * @param shapeType The type of shape to create (e.g., circle, rectangle).
  */
 void
  createShape(ShapeType shapeType);

 /**
  * @brief Called once when the component is initialized.
  */
 void 
  start() override;

 /**
  * @brief Called once per frame to update logic.
  * @param deltaTime Time elapsed since last frame.
  */
 void
  update(float deltaTime) override;

 /**
  * @brief Renders the shape to the given window.
  * @param window Shared pointer to the render target window.
  */
 void
  render(const EngineUtilities::TSharedPointer<Window>& window) override;

 /**
  * @brief Releases any allocated resources or references.
  */
 void
  destroy() override;

 /**
  * @brief Sets the position of the shape using two float values.
  * @param x Horizontal position.
  * @param y Vertical position.
  */
 void 
  setPosition(float x, float y);

 /**
  * @brief Sets the position of the shape using a vector.
  * @param position 2D vector representing the new position.
  */
 void 
  setPosition(const sf::Vector2f& position);

 /**
  * @brief Sets the fill color of the shape.
  * @param color SFML color to apply.
  */
 void 
  setFillColor(const sf::Color& color);

 /**
  * @brief Sets the rotation angle of the shape in degrees.
  * @param angle Rotation in degrees.
  */
 void 
  setRotation(float angle);

 /**
  * @brief Sets the scale of the shape.
  * @param scl 2D vector representing the scale factor.
  */
 void 
  setScale(const sf::Vector2f& scl);

 void
	 setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);

private:
 EngineUtilities::TSharedPointer<sf::Shape> m_shapePtr; ///< Pointer to the SFML shape.
 ShapeType m_shapeType;                                 ///< Type of the shape (circle, rectangle, etc.).
 sf::VertexArray* m_line;                               ///< Optional pointer to a line (not currently used).
};
