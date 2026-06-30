#include "Engine/Core/Engine.h"
#include "Engine/Core/Logger.h"
#include <iostream>

namespace Bake {
	class TestSubsystem final : public Subystem {
	public:
		virtual SubsystemReport OnCreate(Engine* engine) override final {
			Subystem::OnCreate(engine);

			int a = 5;
			Logger::Info("Engine", "Testing {}", a);
			Logger::Warn("Engine", "Testing {}", a);
			Logger::Error("Engine", "Testing {}", a);
			Logger::Critical("Engine", "Testing {}", a);

			return SubsystemReport();
		}

		virtual void OnUpdate() override final {}
		virtual void OnDestroy() override final { std::cout << "Destroyed!\n"; }

		void Hello() { std::cout << "Zenci\n"; }
	};

	class ZenciSubsystem final : public Subystem {
	public:
		virtual SubsystemReport OnCreate(Engine* engine) override final {
			Subystem::OnCreate(engine);
			auto& test = _engine->GetSubsystem<TestSubsystem>();
			test.Hello();

			return SubsystemReport();
		}

		virtual void OnUpdate() override final {}
		virtual void OnDestroy() override final { std::cout << "Destroyed!\n"; }
	};
}

int main() {
	using namespace Bake;
	Engine engine{};
	engine.AddSubsystem<TestSubsystem>();
	engine.AddSubsystem<ZenciSubsystem>();
	engine.Run();
	return 0;
}
