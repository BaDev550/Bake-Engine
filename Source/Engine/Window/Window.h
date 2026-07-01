#pragma once
#include <cstdint>
#include <string>

namespace Bake {
	struct WindowNativeHandles {
		uintptr_t handle = 0;
		uintptr_t instance = 0;
	};

	struct WindowSpecs {
		std::string Title = "Window";
		uint32_t Width = 800;
		uint32_t Height = 800;
	};

	class Window {
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual void PollEvents() = 0;
		[[nodiscard]] virtual WindowNativeHandles GetNativeHandles() const = 0;
		[[nodiscard]] inline bool ShoudClose() const { return _shouldClose; }

		static Window* Create(const WindowSpecs& specs);
	protected:
		WindowSpecs _specs;
		bool _shouldClose = false;
	};
}