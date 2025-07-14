#pragma once
#include "Prerequisites.h"

class Window;

/**
 * @enum ComponentType
 * @brief Defines the various types of components in the ECS system.
 */
enum ComponentType {
    NONE = 0,       ///< No type assigned.
    TRANSFORM = 1,  ///< Transform component (position, rotation, scale).
    SPRITE = 2,     ///< Sprite component (visual representation).
    RENDERER = 3,   ///< Renderer component (draw logic).
    PHYSICS = 4,    ///< Physics component (collisions, forces).
    AUDIOSOURCE = 5,///< Audio source component.
    SHAPE = 6,      ///< Shape component (for primitive shapes).
    TEXTURE = 7     ///< Texture component (image data).
};

/**
 * @class Component
 * @brief Abstract base class for all components used in the ECS system.
 *
 * Components define modular behavior and data that can be attached to entities. Each subclass implements specific behavior.
 */
class Component {
public:

    /**
     * @brief Default constructor.
     */
    Component() = default;

    /**
     * @brief Constructor that initializes the component with a specific type.
     * @param type The type of the component.
     */
    Component(const ComponentType type) : m_type(type) {}

    /**
     * @brief Virtual destructor.
     */
    virtual ~Component() = default;

    /**
     * @brief Called when the component is initialized.
     */
    virtual void start() = 0;

    /**
     * @brief Called every frame to update the component logic.
     * @param deltaTime Time elapsed since the last frame.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Called every frame to render the component.
     * @param window Pointer to the rendering window.
     */
    virtual void render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

    /**
     * @brief Called when the component is destroyed or removed.
     */
    virtual void destroy() = 0;

    /**
     * @brief Returns the type of this component.
     * @return The ComponentType enum value representing the type.
     */
    ComponentType getType() const { return m_type; }

protected:
    ComponentType m_type; ///< The specific type of this component.
};
