/**
 * @file Actor.h
 * @brief ECS Actor entity that holds components and participates in the update/render lifecycle.
 *
 * @details
 * An Actor is an Entity that aggregates components and exposes default lifecycle hooks
 * (`start`, `update`, `render`, `destroy`). It also provides a type-safe utility
 * to retrieve attached components via `getComponent<T>()`, using a dynamic cast on
 * the stored component pointers. When the requested component type is not found, an
 * empty shared pointer is returned.
 *
 * @note This header uses EngineUtilities::TSharedPointer, assumed to be a smart pointer
 * API compatible with `std::shared_ptr` semantics (including `dynamic_pointer_cast`).
 */

#pragma once 
#include "Prerequisites.h"
#include "ECS/Entity.h"
#include "CShape.h"
#include "ECS/Transform.h"
#include "ECS/Texture.h"

 /**
  * @class Actor
  * @brief Represents an entity in the ECS system that contains components and participates in update and render cycles.
  *
  * This class inherits from Entity and provides default implementations of the lifecycle methods. It can have multiple components
  * and provides functionality to retrieve components of a specific type.
  */
class
 Actor : public Entity {
public:
/**
 * @brief Default constructor.
 */
 Actor() = default;

/**
 * @brief Constructs an Actor with a given name.
 * @param actorName Name to assign to the actor.
 */
 Actor(const std::string& actorName);

 /**
  * @brief Default destructor.
  */
 virtual ~Actor() = default;

 /**
  * @brief Called once when the actor is started.
  * Override of base class method.
  * @note This default implementation is empty.
  */
 void
  start() override {};

 /**
  * @brief Called every frame to update the actor's logic.
  * @param deltaTime Time elapsed since the last frame.
  */
 void
  update(float deltaTime) override;

/**
 * @brief Called to render the actor using the provided window.
 * @param window Shared pointer to the rendering window.
 */
 void
  render(const EngineUtilities::TSharedPointer<Window>& window) override;

 /**
  * @brief Called when the actor is destroyed.
  * Override of base class method.
  * @note This default implementation is empty.
  */
 void
  destroy() override {};

 /**
  * @brief Assigns/updates the texture associated to this actor.
  * @param texture Shared pointer to the texture resource to associate with the actor.
  * @note The concrete behavior depends on the implementation (e.g., attaching/updating a Texture component).
  */
 void
  setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);

 /**
  * @brief Gets the actor's display name.
  * @return The current name of this actor.
  */
 std::string getName() const {
  return m_name;
 }

 /**
  * @brief Retrieves a component of the specified type attached to the actor.
  * @tparam T Type of the component to retrieve.
  * @return Shared pointer to the component if found, otherwise an empty pointer.
  * @note This non-const overload searches the inherited `components` array and performs a dynamic cast.
  */
 template<typename T>
 EngineUtilities::TSharedPointer<T> getComponent();

 /**
  * @brief Const-qualified overload that retrieves a component of the specified type.
  * @tparam T Type of the component to retrieve.
  * @return Shared pointer to the component if found, otherwise an empty pointer.
  * @note Delegates to the non-const overload to avoid duplicating logic.
  */
 template<typename T>
 EngineUtilities::TSharedPointer<T> getComponent() const;

private:
 std::string m_name = "Actor"; ///< Name of the actor.
};

template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
 for (auto& component : components) {
  EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
  if (specificComponent) {
   return specificComponent;
  }
 }
 // Return empty shared pointer if not found
 return EngineUtilities::TSharedPointer<T>();
}

template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() const {
 //delegates non const version to avoid duplicates
 return const_cast<Actor*>(this)->template getComponent<T>();
}