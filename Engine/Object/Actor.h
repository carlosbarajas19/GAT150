#pragma once
#include "Component/Component.h"
#include "Object.h"
#include "Math/Transform.h"
#include <memory>
#include <vector>

namespace nc
{
	class Scene;
	class Texture;
	class Renderer;

	class Actor : public Object
	{
	public:

		Actor() {}
		Actor(const Transform& transform ) : transform{ transform } {}

		virtual void Initialize() {}	

		virtual void Update(float dt);
		virtual void Draw(Renderer* renderer);

		virtual void OnCollision(Actor* actor) {}

		void AddChild(std::unique_ptr<Actor> actor);

		template<class T>
		T* AddComponent();

		float GetRadius();


	public:
		bool destroy{ false };
		std::string tag;

		Transform transform;
		Scene* scene{ nullptr };

		Actor* parent{ nullptr };
		
		std::vector<std::unique_ptr<Actor>> children;

		std::vector<std::unique_ptr<Component>> components;
	};

	template<class T>
	inline T* Actor::AddComponent()
	{
		std::unique_ptr<T> component = std::make_unique<T>();
		component->owner = this;

		components.push_back(std::move(component));

		return dynamic_cast<T*>(components.back().get());
	}
}