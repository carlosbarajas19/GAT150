#pragma once
#include "Math/Vector2.h"
#include "Framework/System.h"
#include <SDL.h>
#include <vector>
#include <array>


namespace nc
{
	class InputSystem : public System
	{
	public:

		enum class eKeyState
		{
			Idle, 
			Pressed, 
			Held, 
			Released
		};

		enum class eMouseButton
		{
			Left,
			Middle,
			Right
		};

		void Startup() override;
		void Shutdown() override;
		void Update(float dt) override;

		eKeyState GetKeyState(int id);
		bool IsKeyDown(int id);
		bool IsPreviousKeyDown(int id);

		const Vector2 GetMousePosition() const { return mousePosition; }
		bool IsButtonDown(int id) { return mouseButtonState[id]; }
		bool IsPrevButtonDown(int id) { return prevMouseButtonState[id]; }
		eKeyState GetButtonState(int id);


	private:
		std::vector<Uint8> keyboardState;
		std::vector<Uint8> prevKeyboardState;
		int numKeys;

		Vector2 mousePosition;
		std::array<Uint8, 3> mouseButtonState;
		std::array<Uint8, 3> prevMouseButtonState;
	};

}