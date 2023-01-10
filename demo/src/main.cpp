#define SDL_MAIN_HANDLED
#include <iostream>
#include "engine/coreModule/Game.h"

int main(int argc, char *argv[]) {
	pce::Game game;
	game.Initialize();
	game.Run();
	game.Destroy();
	return 0;
}
