#pragma once
#include "Engine.h"

class Game
{
public:

	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();
	bool IsQuit() { return quit; }

private:
	void UpdateTitle(float dt);
	void UpdateStartLevel(float dt);
	void OnAddPoints(const nc::Event& event);
	void OnPlayerHit(const nc::Event& event);
	void OnPlayerDead(const nc::Event& event);


public:
	std::unique_ptr<nc::Actor> player;
	std::unique_ptr<nc::Engine> engine;
	std::unique_ptr<nc::Scene> scene;

private:
	bool quit = false;
	eState state = eState::Title;
	float stateTimer = 0.0f;

	void (Game:: *stateFunction)(float) = nullptr;
	size_t countEnemies = 2;
	size_t level = 1;
	size_t lives = 0;
	size_t score = 0;


	nc::AudioChannel musicChannel;
	std::shared_ptr<nc::Texture> particleTexture;
	std::shared_ptr<nc::Texture> textTexture;
};