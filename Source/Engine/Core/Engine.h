#pragma once
#include "Engine/Core/Subsystem.h"

#include <vector>
#include <exception>
#include <assert.h>
#include <unordered_map>

namespace Bake {
	class Engine final {
	public:
		Engine();
		~Engine();
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

		void Run();
		void RequestExit(const std::string& reason);

		template<typename T, typename... Args>
		void AddSubsystem(Args&&... args) {
			T* system = new T(std::forward<Args>(args)...);
			_initPendingSystems.push_back(system);
		}

		template<typename T>
		T& GetSubsystem() {
			auto it = _activeLookup.find(typeid(T));
			if (it == _activeLookup.end())
				assert(false);
				//throw std::runtime_error("Failed to find");
			return static_cast<T&>(*_activeSystems[it->second]);
		}
	private:
		bool _exitRequest = false;

		std::vector<Subystem*> _activeSystems;
		std::vector<Subystem*> _initPendingSystems;
		std::unordered_map<std::type_index, size_t> _activeLookup;
	};
}