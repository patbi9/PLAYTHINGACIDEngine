#include "ResourceManager.h"

bool 
ResourceManager::loadTexture(const std::string& fileName, 
							 const std::string& extension) {
	//verificar si la textura ya está cargada
	if (m_textures.find(fileName) != m_textures.end()) {
		return true;
	}

	//crear y cargar la textura
	auto texture = EngineUtilities::MakeShared<Texture>(fileName, extension);
	m_textures[fileName] = texture;
	return true;
}

EngineUtilities::TSharedPointer<Texture>
ResourceManager::getTexture(const std::string& fileName) {

	//buscar la textura
	auto it = m_textures.find(fileName);
	if (it != m_textures.end()) {
		return it->second; // devolver la textura si se encuentra
	}

	//si no se encuentra, retornar una textura default
	std::cerr << "[Resource Manager]: Texture not found: " << fileName << ". Using default texture.\n";

	const std::string defaultKey = "Default";

	//verificar si la textura por defecto ya está cargada
	auto defaultIt = m_textures.find(defaultKey);
	if (defaultIt != m_textures.end()) {
		return defaultIt->second; // devolver la textura por defecto si se encuentra
	}


	// cargar la textura por defecto
	auto defaultTexture = EngineUtilities::MakeShared<Texture>(defaultKey, "png");
	m_textures[defaultKey] = defaultTexture;
	return defaultTexture; // devolver la textura por defecto
}