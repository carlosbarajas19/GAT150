#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"
#include "Engine.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	if (scene->GetActor<Player>())
	{
		nc::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		nc::Vector2 forward = nc::Vector2::Rotate(nc::Vector2::up, transform.rotation);

		float turnAngle = nc::Vector2::SignedAngle(forward, direction.Normalized());
		transform.rotation = transform.rotation + turnAngle * (3 * dt);

		transform.rotation = nc::Lerp(transform.rotation, transform.rotation + turnAngle, dt * 2);
		float angle = nc::Vector2::Angle(direction.Normalized(), forward);

		fireTimer -= dt;
		if (fireTimer <= 0 && angle <= nc::DegToRad(50))
		{
			fireTimer = fireRate;
			
			/*std::vector<nc::Vector2> points = { {-5, -5}, {5, -5}, {0, 10}, {-5, -5} };
			std::shared_ptr<nc::Shape> shape1 = std::make_shared<nc::Shape>(points, nc::Color(nc::RandomRange(0.0f, 1), nc::RandomRange(0.0f, 1), nc::RandomRange(0.0f, 1)));*/

			nc::Transform t = transform;
			t.scale = 0.5f;
			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("particle01.png",scene->engine->Get<nc::Renderer>()), 50);
			projectile->tag = "Enemy";
			scene->AddActor(std::move(projectile));
			scene->engine->Get<nc::AudioSystem>()->PlayAudio("eShoot");
		}
	}

	transform.position += nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
	{
		actor->destroy = true;
		hp -= 1;
		if (hp <= 0) { destroy = true; }
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 200, 1, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("",scene->engine->Get<nc::Renderer>()), 50);
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");

		nc::Event event;
		event.name = "AddPoints";
		event.data = 100;
		scene->engine->Get<nc::EventSystem>()->Notify(event);

	}
}
