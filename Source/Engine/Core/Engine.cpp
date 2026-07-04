#include "Engine/Core/Engine.h"

#include "Engine/Input/InputSubsystem.h"

namespace Bake {
	Engine::Engine() {}
	Engine::~Engine() {}

	void Engine::Run() {
		Logger::Info("Engine", "Starting engine...");

		InitializeSubsystems();

		while (!_exitRequest) {

			for (auto* s : _activeSystems)
				s->OnUpdate();
		}

		DestroySubsystems();

		Memory::Allocator::CheckMemoryLeaks();
	}

	void Engine::RequestExit(const std::string& reason) {
		Logger::Info("Engine", "Exiting reason: {}", reason);
		_exitRequest = true;
	}

	void Engine::InitializeSubsystems() {
		for (size_t i = 0; i < _initPendingSystems.size(); i++) {
			auto* system = _initPendingSystems[i];
			if (SubsystemReport report = system->OnCreate(this)) {
				Logger::Info("Engine", "Subsystem added: {}", system->GetTypeID().name());
				_activeLookup[system->GetTypeID()] = i;
				_activeSystems.push_back(std::move(system));
			}
			else {
				Logger::Error("Engine", "Failed to initialize subsystem error: {}", report.GetMessage());
				Memory::Allocator::destroy<Subsystem>(system);
			}
		}
		_initPendingSystems.clear();
	}

	void Engine::DestroySubsystems() {
		for (auto* s : _activeSystems) {
			s->OnDestroy();
			Memory::Allocator::destroy<Subsystem>(s);
		}
		_activeSystems.clear();
	}
}