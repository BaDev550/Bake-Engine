#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <string>
#include <string_view>

namespace Bake {
	struct SubsystemReport {
		SubsystemReport() = default;
		SubsystemReport(std::string_view message) : _message(message) {}

		explicit operator bool() const { return !_message.empty(); }
		std::string_view GetMessage() const { return _message; }
	private:
		std::string _message;
	};

	class Engine;
	class Subystem {
	public:
		virtual ~Subystem() = default;

		virtual SubsystemReport OnCreate(Engine* engine) { _engine = engine; return {}; }
		virtual void OnUpdate() {}
		virtual void OnDestroy() {}
	protected:
		Engine* _engine;
	};

	class Engine final {
	public:
		template<typename T, typename... Args>
		void AddSubsystem(Args&&... args) {
			T* system = new T(std::forward<Args>(args)...);
			_pendingInitLookup[_initPendingSystems.size()] = std::type_index(typeid(T));
			_initPendingSystems.push_back(system);
		}

		template<typename T>
		T& GetSubsystem() {
			auto* it = _activeLookup.find(typeid(T));
			if (it == _activeLookup.end())
				throw std::runtime_error("Failed to find");
			return *_activeSystems[it->second];
		}

		void Run() {
			for (size_t i = 0; i < _initPendingSystems.size(); i++) {
				auto* system = _initPendingSystems[i];
				if (system->OnCreate(this)) {
					_activeLookup[_pendingInitLookup[i]] = i;
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
	private:
		bool _exitRequest = false;
		std::vector<Subystem*> _activeSystems;
		std::vector<Subystem*> _initPendingSystems;
		std::vector<Subystem*> _destroyPendingSystems;
		std::unordered_map<std::type_index, size_t> _activeLookup;
		std::unordered_map<size_t, std::type_index> _pendingInitLookup;
	};
}