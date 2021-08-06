#include "Engine.h"
#include <SDL_Image.h>
#include <iostream>
#include <SDL.h>

int main(int, char**)
{

	nc::Engine engine;
	engine.Startup();

	engine.Get<nc::Renderer>()->Create("GAT150", 800, 600);

	nc::Scene scene;
	scene.engine = &engine;

	nc::SetFilePath("../Resources");


	std::shared_ptr<nc::Texture> texture = engine.Get<nc::ResourceSystem>()->Get<nc::Texture>("sf2.png", engine.Get<nc::Renderer>());
	
	for (size_t i = 0; i < 10; i++)
	{
		nc::Transform transform{ nc::Vector2{nc::RandomRangeInt(0, 800), nc::RandomRangeInt(0, 600)}, 0.0f, 1.0f };
		std::unique_ptr<nc::Actor> actor = std::make_unique<nc::Actor>(transform, texture);
		scene.AddActor(std::move(actor));
	}

	//create texture
	bool quit = false;
	SDL_Event event;
	float quitTime = engine.time.time + 3.0f;

	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		engine.Update();
		scene.Update(engine.time.deltaTime);

		//std::cout << engine.time.time << std::endl;
		if (engine.time.time >= quitTime) quit = true;
		engine.time.timeScale = 10.0f;

		engine.Get<nc::Renderer>()->BeginFrame();
		
		scene.Draw(engine.Get<nc::Renderer>());
		//nc::Vector2 position{ 300, 300 };
		//engine.Get<nc::Renderer>()->Draw(texture, position, 0.0f, nc::Vector2{3, 3});
		
		engine.Get<nc::Renderer>()->EndFrame();

		/*for (size_t i = 0; i < 50; i++)
		{
			SDL_Rect src{ 32, 64, 32, 64 };
			SDL_Rect dest{ nc::RandomRangeInt(0, screen.x), nc::RandomRangeInt(0,screen.y), 16, 24 };

			SDL_RenderCopy(renderer, texture, &src, &dest);
		}*/
		
	}
	SDL_Quit();

	return 0;
}