#pragma once
#include "PlayerComponent.h"

class PickUpComponent : public PlayerComponent
{
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<PickUpComponent>(*this); }

	void Create() override;

	~PickUpComponent();

	virtual bool Write(const rapidjson::Value& value) const override;

	virtual bool Read(const rapidjson::Value& value) override;

	virtual void OnCollisionEnter(const nc::Event& event);
	virtual void OnCollisionExit(const nc::Event& event);

	virtual void Update() override;

private:



};