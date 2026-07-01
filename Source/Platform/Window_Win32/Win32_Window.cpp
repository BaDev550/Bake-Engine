#include "Platform/Window_Win32/Win32_Window.h"
#include "Engine/Core/Logger.h"

namespace Bake {
	LRESULT CALLBACK Win32_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg) {
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	Win32_Window::Win32_Window(const WindowSpecs& specs) {
		_specs = specs;
		
		WNDCLASS wc{};
		wc.lpfnWndProc = Win32_WindowProc;
		wc.hInstance = _hinstance;
		wc.lpszClassName = _windowClassName;
		RegisterClass(&wc);

		_hwnd = CreateWindowEx(
			0,
			_windowClassName,
			TEXT(_specs.Title.c_str()),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, _specs.Width, _specs.Height,
			nullptr,
			nullptr,
			_hinstance,
			nullptr
		);
		if (_hwnd == nullptr) {
			Logger::Error("Win32_Window", "Failed to create window");
			return;
		}

		ShowWindow(_hwnd, SW_SHOW);
		UpdateWindow(_hwnd);
	}

	Win32_Window::~Win32_Window() {
		if (_hwnd) {
			DestroyWindow(_hwnd);
			_hwnd = nullptr;
		}
		UnregisterClass(_windowClassName, _hinstance);
	}

	WindowNativeHandles Win32_Window::GetNativeHandles() const {
		WindowNativeHandles handles{};
		handles.handle = reinterpret_cast<uintptr_t>(_hwnd);
		handles.instance = reinterpret_cast<uintptr_t>(_hinstance);
		return handles;
	}

	void Win32_Window::PollEvents() {
		MSG msg{};
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				_shouldClose = true;
			}
		}
	}
}