#pragma once
#include "Component/Component.h"
class PickUpComponent : public nc::Component
{
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<PickUpComponent>(*this); }

	~PickUpComponent();

	virtual bool Write(const rapidjson::Value& value) const override;

	virtual bool Read(const rapidjson::Value& value) override;

	virtual void Update() override;

private:



};