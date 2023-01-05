#include <iostream>
#include <nlohmann/json.hpp>
#include <fmt/format.h>
#include <SDL.h>
#include "engine/coreModule/Game.h"

int main(int argc, char *argv[]) {
	pce::Game game;
	game.Initialize();
	game.Run();
	game.Destroy();
	return 0;
}
