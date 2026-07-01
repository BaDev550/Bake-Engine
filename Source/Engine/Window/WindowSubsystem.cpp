#include "Engine/Window/WindowSubsystem.h"
#include "Engine/Core/Engine.h"

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
		return SubsystemReport();
	}

	void Bake::WindowSubsystem::OnUpdate() {
		_window->PollEvents();

		if (_window->ShoudClose())
			_engine->RequestExit("Window closed");
	}

	void Bake::WindowSubsystem::OnDestroy() {
		delete _window;
		_window = nullptr;
	}
}