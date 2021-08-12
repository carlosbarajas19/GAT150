#include "Game.h"

void Game::Initialize()
{
	//create engine
	engine = std::make_unique<nc::Engine>(); // new Engine
	engine->Startup();
	engine->Get<nc::Renderer>()->Create("GAT150", 800, 600);

	//create scene
	scene = std::make_unique<nc::Scene>();
	scene->engine = engine.get();

	nc::SetFilePath("../Resources");

	engine->Get<nc::AudioSystem>()->AddAudio("explosion", "audio/explosion.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("music", "audio/dreams.mp3");
	nc::AudioChannel channel = engine->Get<nc::AudioSystem>()->PlayAudio("music", 1, 1, true);

	std::shared_ptr<nc::Texture> texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("sf2.png", engine->Get<nc::Renderer>());

	for (size_t i = 0; i < 10; i++)
	{
		nc::Transform transform{ nc::Vector2{nc::RandomRangeInt(0, 800), nc::RandomRangeInt(0, 600)}, 0.0f, 1.0f };
		std::unique_ptr<nc::Actor> actor = std::make_unique<nc::Actor>(transform, texture);
		scene->AddActor(std::move(actor));
	}

	//create texture
	SDL_Event event;
	float quitTime = engine->time.time + 3.0f;

	// get font from resource system
	int size = 16;
	std::shared_ptr<nc::Font> font = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/ArcadeClassic.ttf", &size);

	// create font texture
	textTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	// set font texture with font surface
	textTexture->Create(font->CreateSurface("hello world", nc::Color{ 1, 1, 1 }));
	// add font texture to resource system
	engine->Get<nc::ResourceSystem>()->Add("textTexture", textTexture);

	engine->Update();
	scene->Update(engine->time.deltaTime);
	
	engine->Get<nc::AudioSystem>()->AddAudio("pShoot", "Player_Shoot.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("eShoot", "Enemy_Shoot.wav");

	engine->Get<nc::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("PlayerHurt", std::bind(&Game::OnPlayerHit, this, std::placeholders::_1));

	stateFunction = &Game::UpdateTitle;
}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();

}

void Game::Update()
{
	stateTimer += engine->time.deltaTime;;

	//(this->*stateFunction)(dt);

	switch (state)
	{
	case Game::eState::Title:
		if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Pressed)
		{
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 5;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
		UpdateStartLevel(engine->time.deltaTime);
		break;
	case Game::eState::Game:
		/*if (scene->GetActors<Enemy>().size() == 0)
		{
			level++;
			switch (level)
			{
			case 1:
				countEnemies = 3;
				break;
			case 2:
				countEnemies = 7;
				break;
			case 3:
				countEnemies = 15;
				break;
			default:
				countEnemies = 20;
				break;
			}
			state = eState::StartLevel;
		}*/
		break;
	case Game::eState::GameOver:
		break;
	default:
		break;
	}

	engine->Update();
	scene->Update(engine->time.deltaTime);

	//std::cout << engine->time.time << std::endl;
	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Pressed) quit = true;

	if (engine->Get<nc::InputSystem>()->GetButtonState((int)nc::InputSystem::eMouseButton::Right) == nc::InputSystem::eKeyState::Pressed)
	{
		nc::Vector2 position = engine->Get<nc::InputSystem>()->GetMousePosition();
		std::cout << position.x << " " << position.y << std::endl;
	};

	std::shared_ptr<nc::Texture> particle = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("particle01.png", engine->Get<nc::Renderer>());

	if (engine->Get<nc::InputSystem>()->GetButtonState((int)nc::InputSystem::eMouseButton::Left) == nc::InputSystem::eKeyState::Held)
	{
		nc::Vector2 position = engine->Get<nc::InputSystem>()->GetMousePosition();
		engine->Get<nc::ParticleSystem>()->Create(position, 1, 5, particle, 10);
		engine->Get<nc::AudioSystem>()->PlayAudio("explosion", 1, nc::RandomRange(-2.0f, 2.0f));
		musicChannel.SetPitch(nc::RandomRangeInt(0.5f, 2.0f));

	};
}

void Game::Draw()
{
	switch (state)
	{
	case Game::eState::Title:
		/*graphics.SetColor(nc::Color::blue);
		graphics.DrawString(360, 300 + static_cast<int>(std::sin(stateTimer * 500) * 25.0f), "Get Vectored");
		graphics.DrawString(333, 400, "Press Space to Start");*/
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		/*graphics.DrawString(30, 20, std::to_string(score).c_str());
		graphics.DrawString(750, 20, std::to_string(lives).c_str());*/
		break;
	case Game::eState::GameOver:
		/*graphics.SetColor(nc::Color::red);
		graphics.DrawString(360, 400, "GameOver");*/
		break;
	default:
		break;
	}

	/*graphics.SetColor(nc::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(750, 20, std::to_string(lives).c_str());*/

	engine->time.timeScale = 10.0f;

	engine->Get<nc::Renderer>()->BeginFrame();

	scene->Draw(engine->Get<nc::Renderer>());
	engine->Draw(engine->Get<nc::Renderer>());

	nc::Transform t;
	t.position = { 30, 30 };
	engine->Get<nc::Renderer>()->Draw(textTexture, t);


	engine->Get<nc::Renderer>()->EndFrame();
}

void Game::UpdateTitle(float dt)
{
	//if (Core::Input::IsPressed(VK_SPACE))
	//{
	//	stateFunction = &Game::UpdateStartLevel;
	//	//state = eState::StartGame;
	//}
}

void Game::UpdateStartLevel(float dt)
{
	/*if (level == 1)
	{
		scene->AddActor(std::make_unique<Player>(nc::Transform{ nc::Vector2(400, 300), 0, 3 }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Shape.txt"), 1000));
	}

	for (size_t i = 0; i < countEnemies; i++)
	{
		scene->AddActor(std::make_unique<Enemy>(nc::Transform{ nc::Vector2(nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)), nc::RandomRange(0.0f,nc::TwoPi), 2 }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Shape1.txt"), 150));
	}*/

	state = eState::Game;
}

void Game::OnAddPoints(const nc::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerHit(const nc::Event& event)
{
	lives--;
}

void Game::OnPlayerDead(const nc::Event& event)
{
	
	std::cout << std::get<std::string>(event.data) << std::endl;
	state = eState::GameOver;
}
