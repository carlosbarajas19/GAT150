#include "Game.h"

#define MSG(message) std::cout << #message << " Line: "<<__LINE__ <<std::endl;

int main(int, char**)
{
	Game game;
	game.Initialize();

	bool quit = false;
	SDL_Event event;
	while (!quit && !game.IsQuit())
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		game.Update();
		game.Draw();
	}
	SDL_Quit();

	return 0;
}