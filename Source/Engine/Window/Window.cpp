#include "Window.h"

#include "Platform/Window_Win32/Win32_Window.h"

namespace Bake {
    Window* Window::Create(const WindowSpecs& specs)
    {
#ifdef _BAKE_PLATFORM_WINDOWS
        return new Win32_Window(specs);
#else
#error "Unsupported platform!"
#endif
    }
}