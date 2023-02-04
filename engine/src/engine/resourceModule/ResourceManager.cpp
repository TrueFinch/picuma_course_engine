//
// Created by Vladimir on 04.02.2023.
//

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "ResourceManager.h"
#include "logModule/LogManager.h"

using namespace pce::resourceModule;

std::unique_ptr<ResourceManager> ResourceManager::Create(SDL_Renderer* renderer) {
	auto manager = std::unique_ptr<ResourceManager>(new ResourceManager());
	manager->m_renderer = renderer;
	return manager;
}

ResourceManager::ResourceManager() {}

void ResourceManager::AddTexture(const std::string& path) {
	const auto full_path = ASSETS_PREFIX + path;
	auto surface = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>(nullptr, SDL_FreeSurface);
	surface.reset(IMG_Load(full_path.c_str()));
	auto texture = std::shared_ptr<SDL_Texture>(
			SDL_CreateTextureFromSurface(m_renderer, surface.get()),
			[](SDL_Texture* t) { SDL_DestroyTexture(t); }
	);

	m_textures.insert({ path, texture });
}

void ResourceManager::AddTexture(const std::string& path, const std::string& id) {
	if (m_idToPath.count(id)) {
		pce::logWarning("[ResourceManager::AddTexture] specified id = {} is already taken!", id);
	}
	m_idToPath.insert_or_assign(id, path);
	AddTexture(path);
}

void ResourceManager::RemoveTexture(const std::string& id) {
	if (!m_idToPath.count(id) && !m_textures.count(id)) {
		pce::logWarning("[ResourceManager::RemoveTexture] texture with id = {} is not exist!", id);
		return;
	}
	auto resId = id;
	if (m_idToPath.count(id)) {
		resId = m_idToPath.at(id);
		m_idToPath.erase(id);
	}
	m_textures.erase(resId);
}

std::optional<std::weak_ptr<SDL_Texture>> ResourceManager::GetTexture(const std::string& id) {
	if (m_idToPath.count(id)) {
		return m_textures.at(m_idToPath.at(id));
	}
	if (m_textures.count(id)) {
		return m_textures.at(id);
	}
	return std::nullopt;
}
