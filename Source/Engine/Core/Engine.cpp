#include "Engine.h"

namespace Bake {
	Engine::Engine() {}
	Engine::~Engine() {}

	void Engine::Run() {
		for (size_t i = 0; i < _initPendingSystems.size(); i++) {
			auto* system = _initPendingSystems[i];
			if (system->OnCreate(this)) {
				_activeLookup[system->GetTypeID()] = i;
				_activeSystems.push_back(std::move(system));
			}
			else {
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
}