#pragma once
#include "Engine/Defines/Types.h"
#include "Engine/Window/Event/Event.h"
#include "Engine/Memory/Allocator.h"
#include <cstdint>
#include <string>
#include <functional>

namespace Bake {
	struct WindowNativeHandles {
		uptr handle = 0;
		uptr instance = 0;
	};

	using EventCallback = std::function<void(EventBase&)>;

	struct WindowSpecs {
		std::string Title = "Window";
		u32 Width = 800;
		u32 Height = 800;
		EventCallback EventCallback = nullptr;
	};

	class Window {
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual void PollEvents() = 0;
		void SetEventCallback(const EventCallback& callback) { _specs.EventCallback = callback; }
		[[nodiscard]] virtual WindowNativeHandles GetNativeHandles() const = 0;
		
		static Window* Create(const WindowSpecs& specs);
	protected:
		WindowSpecs _specs;
	};
}