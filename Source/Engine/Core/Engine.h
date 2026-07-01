#pragma once
#include "Engine/Core/Subsystem.h"
#include "Engine/Core/Logger.h"
#include "Engine/Memory/Allocator.h"
#include "Engine/Defines/Types.h"

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
			T* system = Memory::Allocator::construct<T>(std::forward<Args>(args)...);
			_initPendingSystems.push_back(system);
		}

		template<typename T>
		T& GetSubsystem() {
			auto it = _activeLookup.find(typeid(T));
			if (it == _activeLookup.end())
				Logger::Assert(false, "Engine", "Failed to find subsystem");
			return static_cast<T&>(*_activeSystems[it->second]);
		}
	private:
		void InitializeSubsystems();
		void DestroySubsystems();

		b8 _exitRequest = false;

		std::vector<Subsystem*> _activeSystems;
		std::vector<Subsystem*> _initPendingSystems;
		std::unordered_map<std::type_index, size_t> _activeLookup;
	};
}