//
// Created by Vladimir on 05.01.2023.
//
#include <iostream>
#include <memory>

#include "Game.h"
#include "SDL.h"

using namespace pce;

Game::Game() : m_window(nullptr, SDL_DestroyWindow), m_renderer(nullptr, SDL_DestroyRenderer) {
}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "[Game::Initialize] ERROR: failed to initialize sdl!" << std::endl;
		return;
	}
	m_window.reset(SDL_CreateWindow(
		nullptr,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		680, 480, SDL_WINDOW_BORDERLESS
	));
	if (!m_window) {
		std::cerr << "[Game::Initialize] ERROR: failed to create sdl window!" << std::endl;
		return;
	}

	m_renderer.reset(SDL_CreateRenderer(
		m_window.get(), -1, 0
	));
	if (!m_renderer) {
		std::cerr << "[Game::Initialize] ERROR: failed to create sdl renderer!" << std::endl;
		return;
	}

	m_isRunning = true;
}

void Game::Run() {
	while (m_isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT: {
				m_isRunning = false;
				break;
			}
			case SDL_KEYDOWN: {
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
					m_isRunning = false;
				}
				break;
			}
		}
	}
}

void Game::Update() {

}

void Game::Render() {

}

void Game::Destroy() {
	m_renderer.reset(nullptr);
	m_window.reset(nullptr);
	SDL_Quit();
}
