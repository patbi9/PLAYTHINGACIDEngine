/** 
 * @file ResourceManager.h
 * @brief Singleton responsible for loading and caching engine resources (textures).
 *
 * @details
 * The ResourceManager provides a global cache for texture resources to avoid
 * duplicate loads and to share instances across the application. Textures are
 * addressed by a string key (typically the file base name) and stored as
 * `EngineUtilities::TSharedPointer<Texture>`.
 *
 * @note Thread-safety is not implied by this interface; synchronize externally
 * if you access it from multiple threads.
 */

#pragma once
#include "Prerequisites.h"
#include "ECS/Texture.h"

/**
 * @class ResourceManager
 * @brief Global cache/loader for texture resources (singleton).
 *
 * @details
 * Use @ref getInstance to access the unique instance. Call @ref loadTexture to
 * load a texture from disk into the cache, and @ref getTexture to retrieve the
 * cached handle. Returned pointers may be empty if the resource was not found/
 * loaded.
 */
class
 ResourceManager {
private:
 /**
  * @brief Private constructor to enforce singleton pattern.
  */
 ResourceManager() = default;

 /**
  * @brief Private destructor.
  */
 ~ResourceManager() = default;

public:
 /**
  * @brief Deleted copy constructor (singleton: non-copyable).
  */
 ResourceManager(const ResourceManager&) = delete;

 /**
  * @brief Deleted copy assignment (singleton: non-assignable).
  */
 ResourceManager& operator=(const ResourceManager&) = delete;

 /**
  * @brief Provides access to the single ResourceManager instance.
  * @return Reference to the global ResourceManager.
  */
 static ResourceManager& getInstance() {
  static ResourceManager instance;
  return instance;
 }

 /**
  * @brief Loads a texture into the cache.
  * @param fileName  Base file name (without extension) used as the cache key.
  * @param extension File extension to append (e.g., "png", "jpg").
  * @return True if the texture was successfully loaded and cached; false otherwise.
  *
  * @details
  * Loads `<fileName>.<extension>` and stores it under @p fileName. If the key
  * already exists, the behavior depends on the implementation (commonly no-op).
  */
 bool
 loadTexture(const std::string& fileName, const std::string& extension);

 /**
  * @brief Retrieves a cached texture by key.
  * @param fileName Cache key used at load time (typically the base file name).
  * @return Shared pointer to the texture if present; otherwise an empty pointer.
  */
 EngineUtilities::TSharedPointer<Texture>
 getTexture(const std::string& fileName);


private:
 /**
  * @brief Texture cache keyed by file name (base name without extension).
  */
 std::unordered_map<std::string, EngineUtilities::TSharedPointer<Texture>> m_textures;
};
