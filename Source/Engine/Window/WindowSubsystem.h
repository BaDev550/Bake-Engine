#pragma once

#include "Engine/Core/Subsystem.h"
#include "Engine/Window/Window.h"

namespace Bake {
	class WindowSubsystem final : public Subsystem {
	public:
		virtual SubsystemReport OnCreate(Engine* engine) override final;
		virtual void OnUpdate() override final;
		virtual void OnDestroy() override final;

		Window& GetWindow() { return *_window; }
	private:
		Window* _window = nullptr;

		void EventCallback(EventBase& e);
	};
}