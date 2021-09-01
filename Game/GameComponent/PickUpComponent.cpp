#include "PickUpComponent.h"
#include "Engine.h"
#include <memory>

using namespace nc;

void PickUpComponent::Create()
{
    owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PickUpComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
    owner->scene->engine->Get<EventSystem>()->Subscribe("collision_exit", std::bind(&PickUpComponent::OnCollisionExit, this, std::placeholders::_1), owner);
    owner->scene->engine->Get<AudioSystem>()->AddAudio("coin", "audio/coin.wav");
}

PickUpComponent::~PickUpComponent()
{
	owner->scene->engine->Get<EventSystem>()->UnSubscribe("collision_enter", owner);
}

bool PickUpComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PickUpComponent::Read(const rapidjson::Value& value)
{
	return true;
}

void PickUpComponent::OnCollisionEnter(const nc::Event& event)
{
    void* p = std::get<void*>(event.data);
    Actor* actor = reinterpret_cast<Actor*>(p);

    if (istring_compare(actor->tag, "player")) {
        owner->scene->engine->Get<AudioSystem>()->PlayAudio("coin");
        owner->destroy = true;

        Event event;
        event.name = "add_score";
        event.data = 10;

        owner->scene->engine->Get<EventSystem>()->Notify(event);
    }
    else return;
}

void PickUpComponent::OnCollisionExit(const nc::Event& event)
{
}

void PickUpComponent::Update()
{

}

