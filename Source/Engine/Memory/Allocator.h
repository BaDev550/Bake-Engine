#pragma once
#include "Engine/Defines/Types.h"
#include <memory>
#include <new>
#include <cstddef>

namespace Bake::Memory {
	class Allocator {
	public:
		static void* allocate(usize size, usize alignment = 16);
		static void free(void* ptr);

		template<typename T, typename... Args>
		static T* construct(Args&&... args) {
			void* memory = allocate(sizeof(T), alignof(T));
			return new (memory) T(std::forward<Args>(args)...);
		}

		template<typename T>
		static void destroy(void* ptr) {
			if (ptr) {
				static_cast<T*>(ptr)->~T();
				free(ptr);
			}
		}

		static void CheckMemoryLeaks();

		[[nodiscard]] static usize GetTotalAllocated();
		[[nodiscard]] static usize GetTotalFreed();
		[[nodiscard]] static usize GetCurrentUsage();
	};
}