//
// Created by Vladimir on 04.02.2023.
//

#include "RenderSystem.h"
#include "ecsModule/components/TransformComponent.h"
#include "ecsModule/components/SpriteComponent.h"

using namespace pce::ecsModule::systems;
using namespace pce::ecsModule;

RenderSystem::RenderSystem() {
	RequireComponent<components::TransformComponent>();
	RequireComponent<components::SpriteComponent>();
}

void RenderSystem::Setup() {

}

void RenderSystem::Update(float deltaTime) {
	for (const auto& entity : GetEntities()) {
		const auto& transform = entity.GetComponent<components::TransformComponent>();
		const auto& sprite = entity.GetComponent<components::SpriteComponent>();

		SDL_Rect objRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				static_cast<int>(sprite.width),
				static_cast<int>(sprite.height)
		};
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(m_renderer, &objRect);
	}
}

void RenderSystem::SetRenderer(SDL_Renderer *renderer) {
	m_renderer = renderer;
}
