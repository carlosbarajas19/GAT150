#include "Player.h"
//#include "Projectile.h"
#include "Engine.h"
#include "Math/MathUtils.h"
//#include "Enemy.h"
#include <memory>

Player::Player(const nc::Transform& transform, std::shared_ptr<nc::Texture> shape, float speed) : nc::Actor{ transform, shape }, speed{ speed } 
{
	
}

void Player::Initialize()
{
	/*std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = nc::Vector2{ 0, -5 };
	AddChild(std::move(locator)); 

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = nc::Vector2{ 0, 5 };
	AddChild(std::move(locator));

	std::unique_ptr engine = std::make_unique<Actor>(nc::Transform(), scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("gun.png"));
	engine->transform.localPosition = nc::Vector2{ -10, 0};
	AddChild(std::move(engine));*/

	/*locator->transform.localPosition = nc::Vector2{ 0, -5 };
	locator->transform.localRotation = nc::DegToRad(180);
	AddChild(std::move(locator));*/
}

void Player::Update(float dt)
{
	Actor::Update(dt);

	//children[2]->transform.localRotation += 5 * dt;

	//movement
	float thrust = 0;
	nc::Vector2 input;
	//std::unique_ptr<nc::Engine> engine;
	
	
	if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == nc::InputSystem::eKeyState::Held) transform.rotation -= 1 * dt;
	if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == nc::InputSystem::eKeyState::Held) transform.rotation += 1 * dt;
	if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == nc::InputSystem::eKeyState::Held) thrust = speed;

	/*if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;*/

	//acceleration
	//nc::Vector2 gravity = (nc::Vector2{ 400, 300 } - transform.position).Normalized() * 200;
	//nc::Vector2 gravity = nc::Vector2::down * 200;
	//acceleration += gravity;

	nc::Vector2 acceleration; 
	acceleration = nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * thrust;
	velocity += acceleration * dt;
	transform.position += velocity * dt;
	velocity *= 0.94f;



	//nc::Vector2::Rotate(nc::Vector2::up, transform.rotation);

	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

	//fire
	//fireTimer -= dt;
	//if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE))
	//{
	//	fireTimer = fireRate;

	//	{
	//		nc::Transform t = children[0]->transform;
	//		t.scale = 0.75f;

	//		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("player_bullet.txt"), 600);
	//		projectile->tag = "Player";
	//		scene->AddActor(std::move(projectile));
	//	}

	//	/*std::vector<nc::Vector2> points = { {-5, -5}, {5, -5}, {0, 10}, {-5, -5} };
	//	std::shared_ptr<nc::Shape> shape1 = std::make_shared<nc::Shape>(points, nc::Color(nc::RandomRange(0.0f, 1), nc::RandomRange(0.0f, 1), nc::RandomRange(0.0f, 1)));*/
	//	
	//	{
	//		nc::Transform t = children[1]->transform;
	//		t.scale = 0.75f;

	//		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("player_bullet.txt"), 600);
	//		projectile->tag = "Player";
	//		scene->AddActor(std::move(projectile));
	//	}
	//	scene->engine->Get<nc::AudioSystem>()->PlayAudio("pShoot");
	//}

	/*std::vector<nc::Color> colors = { nc::Color::white, nc::Color::blue, nc::Color::purple, nc::Color::green, nc::Color::cyan };
	scene->engine->Get<nc::ParticleSystem>()->Create(children[2]->transform.position, 5, 3, colors, 50, children[2]->transform.rotation + nc::DegToRad(180), nc::DegToRad(30));*/
}

void Player::OnCollision(Actor* actor)
{
	/*if (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy")
	{
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 200, 1, nc::Color::white, 50);
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");
		actor->destroy = true;
		if (lives <= 0) 
		{ 
			destroy = true; 

			nc::Event event;
			event.name = "PlayerDead";
			event.data = std::string("yes, I'm dead!");
			scene->engine->Get<nc::EventSystem>()->Notify(event);
		}
		else 
		{
			lives--;

			nc::Event event;
			event.name = "PlayerHurt";
			event.data = std::string("oof!");
			scene->engine->Get<nc::EventSystem>()->Notify(event);
		}
	}

	if (dynamic_cast<Enemy*>(actor))
	{
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 200, 1, nc::Color::white, 50);
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");
		actor->destroy = true;
		if (lives <= 0)
		{
			destroy = true;

			nc::Event event;
			event.name = "PlayerDead";
			event.data = std::string("yes, I'm dead!");
			scene->engine->Get<nc::EventSystem>()->Notify(event);
		}
		else
		{
			lives--;

			nc::Event event;
			event.name = "PlayerHurt";
			event.data = std::string("oof!");
			scene->engine->Get<nc::EventSystem>()->Notify(event);
		}

	}*/

}


