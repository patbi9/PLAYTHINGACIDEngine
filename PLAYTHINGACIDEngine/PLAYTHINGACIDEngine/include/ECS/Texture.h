/**
 * @file Texture.h
 * @brief ECS component that wraps an SFML texture resource.
 *
 * @details
 * The Texture component loads and owns an `sf::Texture` from disk, using a name and
 * optional file extension (default "png"). It sets its component type to
 * `ComponentType::TEXTURE` in the base class. If loading fails, it prints an error
 * to `std::cout` and keeps the internal texture in its default-constructed state.
 *
 * @note This component uses SFML (`sf::Texture`) and depends on the engine's
 * `EngineUtilities::TSharedPointer` for the `render` signature.
 * @warning The constructor does not throw on load failure; it only logs a message.
 */

#pragma once
#include "../Prerequisites.h"
#include "Component.h"

 /**
  * @class Texture
  * @brief Component that manages an image resource as an SFML texture.
  */
class
 Texture : public Component {
public:
 /**
  * @brief Default constructor (does not load any file).
  */
 Texture() = default;

 /**
  * @brief Constructs and attempts to load a texture from file.
  * @param textureName Base name of the file to load (without extension).
  * @param extension Optional file extension (defaults to "png").
  *
  * @details
  * Attempts to load `<textureName>.<extension>` into the internal `sf::Texture`.
  * Sets the base @ref Component type to `ComponentType::TEXTURE`.
  *
  * @note On failure, writes an error message to `std::cout`.
  */
 Texture(const std::string& textureName, 
	     const std::string& extension = "png") :
  m_textureName(textureName), m_extension(extension), Component(ComponentType::TEXTURE) {
  if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
   std::cout << "Error de carga de textura: " << m_textureName << "." << m_extension << std::endl;
  }
 }

 /**
  * @brief Virtual default destructor.
  */
 virtual
  ~Texture() = default;

 /**
  * @brief Lifecycle hook called once at component start.
  * @note No-op in this implementation.
  */
 void
  start() override {};

 /**
  * @brief Per-frame update hook.
  * @param deltaTime Time elapsed since the previous frame.
  * @note No-op in this implementation.
  */
 void
  update(float deltaTime) override {};

 /**
  * @brief Render hook with the engine window/context.
  * @param window Shared pointer to the rendering window/context.
  * @note No-op in this implementation.
  */
 void
  render(const EngineUtilities::TSharedPointer<Window>& window) override {};

 /**
  * @brief Lifecycle hook called on component destruction/teardown.
  * @note No-op in this implementation.
  */
 void
  destroy() override {};

 /**
  * @brief Accessor for the underlying SFML texture.
  * @return Reference to the owned `sf::Texture`.
  * @warning Returns a non-const reference; callers can mutate the texture.
  */
 sf::Texture&
  getTexture() {
  return m_texture;
 }

private:
 /** @brief Underlying SFML texture resource. */
 sf::Texture m_texture;
 /** @brief Base filename (without extension) used to load the texture. */
 std::string m_textureName;
 /** @brief File extension used during load (e.g., "png", "jpg"). */
 std::string m_extension;
};
