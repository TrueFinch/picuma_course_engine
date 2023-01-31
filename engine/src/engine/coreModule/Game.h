//
// Created by Vladimir on 05.01.2023.
//

#pragma once

#include <memory>
#include <SDL2/SDL.h>

// TODO remove "engine/" prefix with cmake configuration somehow
#include "engine/utilsModule/types.h"

namespace pce {


	class Game final {
	public:
		explicit Game();

		~Game() = default;

		void Initialize();

		void Run();

		void Destroy();

	private:
		void ProcessInput();

		void Delay() const;

		void Update();

		void Render();

		bool m_isRunning = false;
		float m_deltaTime = 0;
		uint32 m_prevFrameMillis = 0;
		//TODO move to settings file and left ability to change from game
		bool m_capFPS = true;
		uint32 m_fps = 60;
		uint32 m_milliPerFrame = 1000 / m_fps;
		//
		std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
		std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
	};

} // pce
