#include "Engine/Window/WindowSubsystem.h"
#include "Engine/Core/Engine.h"
#include "Engine/Memory/Allocator.h"

namespace Bake {
	SubsystemReport WindowSubsystem::OnCreate(Engine* engine) {
		Subsystem::OnCreate(engine);

		WindowSpecs specs{};
		specs.Title = "Bake Engine";
		specs.Width = 800;
		specs.Height = 800;
		_window = Window::Create(specs);
		if (!_window)
			return SubsystemReport("Failed to create window!");
		_window->SetEventCallback([this](EventBase& e) { this->EventCallback(e); });
		return SubsystemReport();
	}

	void WindowSubsystem::OnUpdate() {
		_window->PollEvents();
	}

	void WindowSubsystem::OnDestroy() {
		ClearKeyCallback();
		_window->ClearEventCallback();
		Memory::Allocator::destroy<Window>(_window);
	}

	void WindowSubsystem::EventCallback(EventBase& e) {
		if (e.GetEventType() == EventType::WindowClosed)
			_engine->RequestExit("Window closed");

		if (e.GetEventType() == EventType::KeyPressed) {
			KeyPressedEvent& keyEvent = static_cast<KeyPressedEvent&>(e);
			_keyCallback(keyEvent.GetKeyCode(), true);
		}
		else if (e.GetEventType() == EventType::KeyReleased) {
			KeyReleasedEvent& keyEvent = static_cast<KeyReleasedEvent&>(e);
			_keyCallback(keyEvent.GetKeyCode(), false);
		}
	}
}