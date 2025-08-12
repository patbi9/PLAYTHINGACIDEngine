#pragma once
#include "../Prerequisites.h"
#include "Component.h"

class
	Texture : public Component {
public:
	Texture() = default;

	Texture(const std::string& textureName, const std::string& extension = "png") :
		m_textureName(textureName), m_extension(extension), Component(ComponentType::TEXTURE) {
		if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
			std::cout << "Error de carga de textura: " << m_textureName << "." << m_extension << std::endl;
		}
	}

	virtual
		~Texture() = default;

	void
		start() override {};

	void
		update(float deltaTime) override {};

	void
		render(const EngineUtilities::TSharedPointer<Window>& window) override {};

	void
		destroy() override {};

	sf::Texture&
		getTexture() {
		return m_texture;
	}

private:
	sf::Texture m_texture;
	std::string m_textureName;
	std::string m_extension;
};