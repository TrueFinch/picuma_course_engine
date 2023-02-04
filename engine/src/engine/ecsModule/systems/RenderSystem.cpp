//
// Created by Vladimir on 04.02.2023.
//

#include "RenderSystem.h"

#include "ecsModule/components/TransformComponent.h"
#include "ecsModule/components/SpriteComponent.h"
#include "resourceModule/ResourceManager.h"

using namespace pce::ecsModule::systems;
using namespace pce::ecsModule;

RenderSystem::RenderSystem() {
	RequireComponent<components::TransformComponent>();
	RequireComponent<components::SpriteComponent>();
}

void RenderSystem::Setup() {

}

void RenderSystem::Update(float deltaTime) {
	for (const auto& entity: GetEntities()) {
		const auto& transform = entity.GetComponent<components::TransformComponent>();
		const auto& sprite = entity.GetComponent<components::SpriteComponent>();
		auto& resourceManager = resourceModule::ResourceManagerInstance::GetInstance();
		auto texture = resourceManager.GetTexture(sprite.id)->lock();

		int spriteW, spriteH;
		if (!sprite.size) {
			SDL_QueryTexture(texture.get(), nullptr, nullptr, &spriteW, &spriteH);
		} else {
			spriteW = static_cast<int>(sprite.size->x);
			spriteH = static_cast<int>(sprite.size->y);
		}

		SDL_Rect srcRect = { sprite.srcRectPos.x, sprite.srcRectPos.y, spriteW, spriteH };
		SDL_Rect dstRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				static_cast<int>(static_cast<float>(spriteW) * transform.scale.x),
				static_cast<int>(static_cast<float>(spriteH) * transform.scale.y),
		};

		SDL_RenderCopyEx(
				m_renderer,
				resourceManager.GetTexture(sprite.id)->lock().get(),
				&srcRect,
				&dstRect,
				transform.rotation,
				nullptr,
				sprite.flip
		);
	}
}

void RenderSystem::SetRenderer(SDL_Renderer* renderer) {
	m_renderer = renderer;
}
