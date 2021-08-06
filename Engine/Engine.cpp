#include "Engine.h"

namespace nc
{
	void Engine::Startup()
	{
		systems.push_back(std::make_unique<Renderer>());
		systems.push_back(std::make_unique<EventSystem>());
		systems.push_back(std::make_unique<ResourceSystem>());

		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->Startup(); });

		//std::for_each(systems.begin(), systems.end(), [](auto& system) {system->Startup(); });
	}

	void Engine::Shutdown()
	{
		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->Shutdown(); });
	}

	void Engine::Update()
	{
		time.Tick();
		std::for_each(systems.begin(), systems.end(), [this](auto& system) {system->Update(this->time.deltaTime); });


	}

	void Engine::Draw()
	{
	}
}