#include "Engine/Core/Engine.h"

namespace Bake {
	Engine::Engine() {}
	Engine::~Engine() {}

	void Engine::Run() {
		for (size_t i = 0; i < _initPendingSystems.size(); i++) {
			auto* system = _initPendingSystems[i];
			if (SubsystemReport report = system->OnCreate(this)) {
				Logger::Info("Engine", "Subsystem added: {}", system->GetTypeID().name());
				_activeLookup[system->GetTypeID()] = i;
				_activeSystems.push_back(std::move(system));
			}
			else {
				Logger::Error("Engine", "Failed to initialize subsystem error: {}", report.GetMessage());
				delete system;
				system = nullptr;
			}
		}
		_initPendingSystems.clear();

		while (!_exitRequest) {

			for (auto* s : _activeSystems)
				s->OnUpdate();
		}

		for (auto* s : _activeSystems) {
			s->OnDestroy();
			delete s;
			s = nullptr;
		}
		_activeSystems.clear();
	}

	void Engine::RequestExit(const std::string& reason) {
		Logger::Info("Engine", "Exiting reason: {}", reason);
		_exitRequest = true;
	}
}