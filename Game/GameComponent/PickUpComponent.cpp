#include "PickUpComponent.h"
#include "Engine.h"
using namespace nc;

PickUpComponent::~PickUpComponent()
{
}

bool PickUpComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PickUpComponent::Read(const rapidjson::Value& value)
{
	return true;
}

void PickUpComponent::Update()
{

}
