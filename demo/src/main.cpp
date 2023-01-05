#include <iostream>
#include <nlohmann/json.hpp>
#include <fmt/format.h>
#include <SDL.h>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "Hello, World!" << std::endl;
    SDL_Window* w = SDL_CreateWindow(
        nullptr,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_BORDERLESS
    );
    SDL_Renderer* r = SDL_CreateRenderer(w, -1, 0);
    /* Pauses all SDL subsystems for a variable amount of milliseconds */
    SDL_Delay(3000);

    /* Frees memory */
    SDL_DestroyWindow(w);

    /* Shuts down all SDL subsystems */
    SDL_Quit();
    return 0;
}
