/**
 * @file Transform.h
 * @brief ECS component for 2D spatial transforms (position, rotation, scale).
 *
 * @details
 * The Transform component stores position, rotation, and scale in 2D space and
 * provides basic setters/getters plus a simple steering helper (`seek`) that moves
 * the entity toward a target position when outside a given range.
 *
 * @note Rotation is represented as a 2D vector. Its semantic meaning depends on
 * the engine convention (e.g., storing yaw/pitch or an angle plus auxiliary data).
 * @warning Raw pointer accessors (`getPosData`, `getRotData`, `getScaData`) expose
 * underlying memory; use with care and ensure the object outlives any external use.
 */

#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Math/EngineMath.h"
using sf::Vector2f;

class Window;

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
		       scale(1.0f, 1.0f){
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

 /**
  * @brief Simple steering behavior that moves toward a target if outside a radius.
  *
  * @param targetPosition Target world position to seek.
  * @param speed Movement speed in world units per second.
  * @param deltaTime Time step (seconds) since the previous frame.
  * @param range Do-nothing radius; if the distance to target is <= range, no move.
  *
  * @details
  * Computes a normalized direction toward @p targetPosition and advances the
  * current @ref position by `direction * speed * deltaTime` only when the distance
  * to the target is greater than @p range.
  */
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
 * @brief Provides raw pointer access to the position data (x, y).
 * @return Pointer to the first float component of @ref position.
 * @warning Exposes internal storage; ensure lifetime and avoid aliasing issues.
 */
 float*
  getPosData() {
  return &position.x;
 }

 /**
  * @brief Provides raw pointer access to the rotation data (x, y).
  * @return Pointer to the first float component of @ref rotation.
  * @warning Exposes internal storage; ensure lifetime and avoid aliasing issues.
  */
 float*
  getRotData() {
  return &rotation.x;
 }

 /** 
 * @brief Provides raw pointer access to the scale data (x, y).
 * @return Pointer to the first float component of @ref scale.
 * @warning Exposes internal storage; ensure lifetime and avoid aliasing issues.
 */
 float*
  getScaData() {
  return &scale.x;
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
