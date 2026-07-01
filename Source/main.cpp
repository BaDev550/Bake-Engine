#include "Engine/Core/Engine.h"
#include "Engine/Core/Logger.h"
#include "Engine/Window/WindowSubsystem.h"
#include <iostream>

int main(int argc, char** argv) {
	using namespace Bake;
	Engine engine{};
	engine.AddSubsystem<WindowSubsystem>();
	engine.Run();
	return 0;
}
