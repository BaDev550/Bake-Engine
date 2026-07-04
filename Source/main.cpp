#include "Engine/Core/Engine.h"
#include "Engine/Core/Logger.h"
#include "Engine/Window/WindowSubsystem.h"
#include "Engine/Input/InputSubsystem.h"
#include <iostream>

int main(int argc, char** argv) {
	using namespace Bake;
	Engine engine{};
	engine.AddSubsystem<WindowSubsystem>();
	engine.AddSubsystem<InputSubsystem>();
	engine.Run();
	return 0;
}
