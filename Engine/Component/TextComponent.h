#pragma once
#include "GraphicsComponent.h"

namespace nc
{
	class TextComponent : public GraphicsComponent
	{
	public:

		std::unique_ptr<Object> Clone() const { return std::make_unique<TextComponent>(*this); }
	};
}