//
// Created by Vladimir on 04.02.2023.
//

#pragma once

#include <SDL2/SDL.h>
#include "engine/ecsModule/ECS.h"

namespace pce::ecsModule::systems {
	class RenderSystem : public System {
	public:
		explicit RenderSystem();

		void Setup() override;

		void Update(float deltaTime) override;

		void Teardown() override {}

		void SetRenderer(SDL_Renderer* renderer);
	private:
		//TODO replace with smart pointer
		SDL_Renderer* m_renderer = nullptr;
	};
}
