#pragma once
#include "Prerequisites.h"
#include "ECS/Entity.h"
#include "CShape.h"
#include "ECS/Transform.h"

/**
 * @class Actor
 * @brief Represents an entity in the ECS system that contains components and participates in update and render cycles.
 *
 * This class inherits from Entity and provides default implementations of the lifecycle methods. It can have multiple components
 * and provides functionality to retrieve components of a specific type.
 */
class Actor : Entity {

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
     */
    void start() override {};

    /**
     * @brief Called every frame to update the actor's logic.
     * @param deltaTime Time elapsed since the last frame.
     */
    void update(float deltaTime) override;

    /**
     * @brief Called to render the actor using the provided window.
     * @param window Shared pointer to the rendering window.
     */
    void render(const EngineUtilities::TSharedPointer<Window>& window) override;

    /**
     * @brief Called when the actor is destroyed.
     * Override of base class method.
     */
    void destroy() override {};

    /**
     * @brief Retrieves a component of the specified type attached to the actor.
     * @tparam T Type of the component to retrieve.
     * @return Shared pointer to the component if found, otherwise an empty pointer.
     */
    template<typename T>
    EngineUtilities::TSharedPointer<T> getComponent();

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
