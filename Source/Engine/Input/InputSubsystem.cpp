#include "InputSubsystem.h"
#include "Engine/Core/Engine.h"

namespace Bake {
	SubsystemReport InputSubsystem::OnCreate(Engine* engine) {
		Subsystem::OnCreate(engine);

		engine->GetSubsystem<WindowSubsystem>().SetKeyCallback([this](u16 key, bool pressed) { this->KeyCallback(key, pressed); }); // TODO(0x): find a better way to handle even callbacks!

		return SubsystemReport();
	}

	void InputSubsystem::OnUpdate() {}
	void InputSubsystem::OnDestroy() {}

	bool InputSubsystem::IsKeyPressed(KeyCode key) const {
		return _keyStates.find(key) == _keyStates.end() ? false : _keyStates.at(key);
	}

	bool InputSubsystem::IsKeyReleased(KeyCode key) const {
		return _keyStates.find(key) == _keyStates.end() ? false : !_keyStates.at(key);
	}

	void InputSubsystem::KeyCallback(u16 key, bool pressed) {
		_keyStates[static_cast<KeyCode>(key)] = pressed;
	}
}