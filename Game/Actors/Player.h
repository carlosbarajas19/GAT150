#pragma once
#include "Object/Actor.h"

class Player : public nc::Actor
{
public:
	
	Player() {}
	Player(const nc::Transform& transform, std::shared_ptr<nc::Texture> shape, float speed);

	void Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

	size_t GetLives() { return lives; }
	void SetLives(size_t& newHp) { lives = newHp; }

private:
	size_t lives = 5;
	float speed = 300;
	float fireRate { 0.2f };
	float fireTimer { 0 };
	nc::Vector2 velocity;
};