#pragma once
#include "Engine/Input/Keycodes.h"
#include "Engine/Core/Subsystem.h"
#include "Engine/Window/WindowSubsystem.h"
#include <array>

namespace Bake {
	class InputSubsystem final : public Subsystem {
	public:
		virtual SubsystemReport OnCreate(Engine* engine);
		virtual void OnUpdate();
		virtual void OnDestroy();

		bool IsKeyPressed(KeyCode key) const;
		bool IsKeyReleased(KeyCode key) const;
	private:
		std::unordered_map<KeyCode, bool> _keyStates;

		void KeyCallback(u16 key, bool pressed);
	};
}