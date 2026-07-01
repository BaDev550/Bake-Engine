#include "Engine/Core/Engine.h"
#include "Engine/Core/Logger.h"
#include "Engine/Window/WindowSubsystem.h"
#include <iostream>

namespace Bake {
	class TestSubsystem final : public Subsystem {
	public:
		virtual SubsystemReport OnCreate(Engine* engine) override final {
			Subsystem::OnCreate(engine);
			return SubsystemReport();
		}

		virtual void OnUpdate() override final {}
		virtual void OnDestroy() override final {}

		void Hello() { Logger::Info("TestSubsystem", "Zenci"); }
	};

	class ZenciSubsystem final : public Subsystem {
	public:
		virtual SubsystemReport OnCreate(Engine* engine) override final {
			Subsystem::OnCreate(engine);
			auto& test = _engine->GetSubsystem<TestSubsystem>();
			test.Hello();

			return SubsystemReport();
		}

		virtual void OnUpdate() override final {}
		virtual void OnDestroy() override final {}
	};
}

int main(int argc, char** argv) {
	using namespace Bake;
	Engine engine{};
	engine.AddSubsystem<TestSubsystem>();
	engine.AddSubsystem<ZenciSubsystem>();
	engine.AddSubsystem<WindowSubsystem>();
	engine.Run();
	return 0;
}
