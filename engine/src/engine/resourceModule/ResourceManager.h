//
// Created by Vladimir on 04.02.2023.
//

#pragma once

#include <optional>
#include <string>
#include <map>

#include <SDL2/SDL.h>

#include "utilsModule/Instance.h"

namespace pce::resourceModule {
	class ResourceManager final {
	public:
		~ResourceManager() = default;

		ResourceManager(const ResourceManager&) = delete;

		ResourceManager(ResourceManager&&) = delete;

		ResourceManager& operator=(const ResourceManager&) = delete;

		ResourceManager& operator=(ResourceManager&&) = delete;

		[[nodiscard]] static std::unique_ptr<ResourceManager> Create(SDL_Renderer* renderer);

		void AddTexture(const std::string& path);

		void AddTexture(const std::string& path, const std::string& id);

		void RemoveTexture(const std::string& id);

		[[nodiscard]] std::optional<std::weak_ptr<SDL_Texture>> GetTexture(const std::string& id);

	protected:
		ResourceManager();

	private:
		std::map<std::string, std::shared_ptr<SDL_Texture>> m_textures;
		std::map<std::string, std::string> m_idToPath;
		//TODO: replace with smart pointer check if
		SDL_Renderer* m_renderer = nullptr;

		inline static const std::string ASSETS_PREFIX = "../assets/";
	};

	class ResourceManagerInstance final : public utilsModule::Instance<ResourceManager> {};
}