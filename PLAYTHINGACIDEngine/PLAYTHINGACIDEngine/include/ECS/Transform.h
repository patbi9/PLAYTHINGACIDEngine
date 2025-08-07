#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Math/EngineMath.h"
using sf::Vector2f;

/**
 * @class Transform
 * @brief Component that handles position, rotation, and scale in 2D space.
 *
 * This component is typically attached to entities that require spatial transformations.
 */
class 
 Transform : public Component
{
public:
 /**
  * @brief Default constructor that initializes the transform to default values.
  * Position = (0, 0), Rotation = (0, 0), Scale = (1, 1)
  */
 Transform() : Component(ComponentType::TRANSFORM),
  position(0.0f, 0.0f),
  rotation(0.0f, 0.0f),
  scale(1.0f, 1.0f)
  {
  }

 /**
  * @brief Called when the component is initialized.
  */
 void
  start() override {};

 /**
  * @brief Updates the component logic (no-op for transform).
  * @param deltaTime Time elapsed since last frame.
  */
 void 
  update(float deltaTime) override {}

 /**
  * @brief Renders the component (no-op for transform).
  * @param window Shared pointer to the rendering window.
  */
 void 
  render(const EngineUtilities::TSharedPointer<Window>& window) override {}

 /**
  * @brief Called when the component is destroyed.
  */
 void
  destroy() override {}

 void
	 seek(const sf::Vector2f& targetPosition,
		 float speed,
		 float deltaTime,
		 float range) {
	 sf::Vector2f direction = targetPosition - position;
	 float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	 if (length > range) {
		 direction /= length; //normalizar el vector
		 position += direction * speed * deltaTime;
	 }
 }

 /**
  * @brief Sets the position of the transform.
  * @param pos A 2D vector representing the new position.
  */
 void
  setPosition(const Vector2f& pos) {
  position = pos;
 }

 /**
  * @brief Sets the rotation of the transform.
  * @param rot A 2D vector representing the rotation angles.
  */
 void
  setRotation(const Vector2f& rot) {
  rotation = rot;
 }

 /**
  * @brief Sets the scale of the transform.
  * @param scl A 2D vector representing the scale factors.
  */
 void
  setScale(const Vector2f& scl) {
  scale = scl;
 }

 /**
  * @brief Gets the current position.
  * @return A 2D vector representing the position.
  */
 Vector2f
  getPosition() const {
  return position;
 }

 /**
  * @brief Gets the current rotation.
  * @return A 2D vector representing the rotation.
  */
 Vector2f
  getRotation() const {
  return rotation;
 }

 /**
  * @brief Gets the current scale.
  * @return A 2D vector representing the scale.
  */
 Vector2f
  getScale() const {
  return scale;
 }

 /**
  * @brief Virtual destructor.
  */
 virtual ~Transform() = default;

private:
 Vector2f position; ///< Position in 2D space.
 Vector2f rotation; ///< Rotation angles (could represent Euler angles or axis).
 Vector2f scale;    ///< Scaling factors.
};
