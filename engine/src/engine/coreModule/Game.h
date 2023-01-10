//
// Created by Vladimir on 05.01.2023.
//

#pragma once

#include <memory>
#include "SDL.h"

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
		void Update();
		void Render();

		bool m_isRunning = false;
		std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
		std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
	};

} // pce
