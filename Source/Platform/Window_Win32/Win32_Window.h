#pragma once
#include "Engine/Window/Window.h"
#include <Windows.h>

namespace Bake {
	class Win32_Window final : public Window {
	public:
		Win32_Window(const WindowSpecs& specs);
		~Win32_Window();
		[[nodiscard]] virtual WindowNativeHandles GetNativeHandles() const final override;

		virtual void PollEvents() final override;
	private:
		HWND _hwnd = nullptr;
		HINSTANCE _hinstance = nullptr;

		const char* _windowClassName = "Win32_Window_Class";
	};
}