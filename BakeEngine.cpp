#include "BakeEngine.h"

using namespace std;

namespace Bake {
	class TestSubsystem final : public Subystem {
	public:
		virtual SubsystemReport OnCreate(Engine* engine) override final {
			Subystem::OnCreate(engine);
			std::cout << "Created!\n";
			return {};
		}

		virtual void OnUpdate() override final { 
			std::cout << "Update!\n";
		}

		virtual void OnDestroy() override final { std::cout << "Destroyed!\n"; }
	};
}

int main() {
	using namespace Bake;
	Engine engine{};
	engine.AddSubsystem<TestSubsystem>();
	engine.Run();
	return 0;
}
