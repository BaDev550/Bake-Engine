#pragma once
#include "Engine/Defines/Types.h"
#include "Engine/Memory/Allocator.h"
#include <cstdint>
#include <string>

namespace Bake {
	struct WindowNativeHandles {
		uptr handle = 0;
		uptr instance = 0;
	};

	struct WindowSpecs {
		std::string Title = "Window";
		u32 Width = 800;
		u32 Height = 800;
	};

	class Window {
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual void PollEvents() = 0;
		[[nodiscard]] virtual WindowNativeHandles GetNativeHandles() const = 0;
		[[nodiscard]] inline b8 ShoudClose() const { return _shouldClose; }

		static Window* Create(const WindowSpecs& specs);
	protected:
		WindowSpecs _specs;
		b8 _shouldClose = false;
	};
}