#include "Platform/Window_Win32/Win32_Window.h"
#include "Engine/Core/Logger.h"

namespace Bake {
	LRESULT CALLBACK Win32_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		WindowSpecs* data = nullptr;
		if (uMsg == WM_NCCREATE) {
			CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
			data = reinterpret_cast<WindowSpecs*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(data));
		}
		else {
			data = reinterpret_cast<WindowSpecs*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		}

		if (data) {
			switch (uMsg) {
			case WM_CLOSE: {
				WindowClosedEvent e;
				if (data->EventCallback) data->EventCallback(e);

				PostQuitMessage(0);
				return 0;
			}
			case WM_SIZE: {
				u32 newWidth = LOWORD(lParam);
				u32 newHeight = HIWORD(lParam);
				data->Width = newWidth;
				data->Height = newHeight;

				WindowResizedEvent e(newWidth, newHeight);
				if (data->EventCallback) data->EventCallback(e);
				break;
			}
			case WM_KEYDOWN: {
				u32 key = static_cast<u32>(wParam);
				KeyPressedEvent e(key);
				if (data->EventCallback) data->EventCallback(e);
				break;
			}
			case WM_MOUSEMOVE: { break; }
			case WM_MOUSEHWHEEL: { break; }
			case WM_SETFOCUS: {
				WindowFocusedEvent e;
				if (data->EventCallback) data->EventCallback(e);
				break;
			}
			case WM_KILLFOCUS: {
				WindowLostFocusEvent e;
				if (data->EventCallback) data->EventCallback(e);
				break;
			}
			}
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
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
			&_specs
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
		handles.handle = reinterpret_cast<uptr>(_hwnd);
		handles.instance = reinterpret_cast<uptr>(_hinstance);
		return handles;
	}

	void Win32_Window::PollEvents() {
		MSG msg{};
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}