#pragma once

#include "Engine/Core/Subsystem.h"
#include "Engine/Window/Window.h"

namespace Bake {
	using KeyCallback = std::function<void(u16, bool)>;

	class WindowSubsystem final : public Subsystem {
	public:
		virtual SubsystemReport OnCreate(Engine* engine) override final;
		virtual void OnUpdate() override final;
		virtual void OnDestroy() override final;

		void SetKeyCallback(const KeyCallback& callback) { _keyCallback = callback; }
		void ClearKeyCallback() { _keyCallback = nullptr; }

		Window& GetWindow() { return *_window; }
	private:
		Window* _window = nullptr;

		KeyCallback _keyCallback;

		void EventCallback(EventBase& e);
	};
}