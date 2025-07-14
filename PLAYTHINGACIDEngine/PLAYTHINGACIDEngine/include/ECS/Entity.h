#pragma once

#include "Prerequisites.h"
#include "Component.h"

class Window;

/**
 * @class Entity
 * @brief Abstract base class for all game entities in the ECS system.
 *
 * Entities act as containers for components. Logic and rendering are delegated to the attached components.
 */
class Entity
{
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~Entity() = default;

    /**
     * @brief Initializes the entity and its components.
     */
    virtual void start() = 0;

    /**
     * @brief Updates the entity and its components every frame.
     * @param deltaTime Time elapsed since the last frame.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Renders the entity and its components.
     * @param window Pointer to the rendering window.
     */
    virtual void render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

    /**
     * @brief Destroys the entity and cleans up its components.
     */
    virtual void destroy() = 0;

    /**
     * @brief Adds a component to the entity.
     * @tparam T The type of the component to add. Must inherit from Component.
     * @param component A shared pointer to the component to add.
     */
    template<typename T>
    void addComponent(EngineUtilities::TSharedPointer<T> component) {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
        components.push_back(component.template dynamic_pointer_cast<Component>());
    }

    /**
     * @brief Retrieves a component of a specific type from the entity.
     * @tparam T The type of the component to retrieve.
     * @return A shared pointer to the component if found, or an empty shared pointer otherwise.
     */
    template<typename T>
    EngineUtilities::TSharedPointer<T> getComponent() {
        for (auto& component : components) {
            EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
            if (specificComponent) {
                return specificComponent;
            }
        }
        return EngineUtilities::TSharedPointer<T>();
    }

protected:
    bool isActive; ///< Indicates whether the entity is active in the scene.
    uint32_t id; ///< Unique identifier for the entity.
    std::vector<EngineUtilities::TSharedPointer<Component>> components; ///< List of components attached to the entity.
};
