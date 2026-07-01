#include "Engine/Memory/Allocator.h"
#include "Engine/Core/Logger.h"
#include <unordered_map>

namespace Bake::Memory {
	struct MemoryBlock {
		usize size;
		usize alignment;
	};

	struct MemoryMetrics final {
		void RecordAllocation(void* ptr, usize size, usize alignment) {
			totalAllocated += size;
			_allocatedBlocks[ptr] = MemoryBlock{ size, alignment };
		}

		[[nodiscard]] MemoryBlock RecordDeallocation(void* ptr) {
			auto it = _allocatedBlocks.find(ptr);
			if (it != _allocatedBlocks.end()) {
				totalFreed += it->second.size;
				MemoryBlock block = it->second;
				_allocatedBlocks.erase(it);
				return block;
			}
			else {
				Logger::Warn("MemoryMetrics", "Attempted to free untracked memory at address: {}", ptr);
				return MemoryBlock{ 0, 0 };
			}
		}
		[[nodiscard]] inline usize GetCurrentUsage() const { return totalAllocated - totalFreed; }
		
		void CheckMemoryLeaks() const {
			if (!_allocatedBlocks.empty()) {
				Logger::Warn("MemoryMetrics", "Memory leak detected! {} blocks not freed.", _allocatedBlocks.size());
				for (const auto& [ptr, block] : _allocatedBlocks) {
					Logger::Warn("MemoryMetrics", "Leaked block at address: {}, size: {}, alignment: {}", ptr, block.size, block.alignment);
				}
			}
			else if (totalAllocated > totalFreed) {
				Logger::Warn("MemoryMetrics", "Out of tracking memory leak detected! Total allocated: {}, total freed: {}, current usage: {}", totalAllocated, totalFreed, GetCurrentUsage());
			}
			else {
				Logger::Info("MemoryMetrics", "No memory leaks detected.");
			}
		}

		usize totalAllocated = 0;
		usize totalFreed = 0;
		std::unordered_map<void*, MemoryBlock> _allocatedBlocks;
	};

	MemoryMetrics _memMetrics;

    void* Allocator::allocate(usize size, usize alignment) {
		void* mem = ::operator new(size, std::align_val_t(alignment));
		_memMetrics.RecordAllocation(mem, size, alignment);
		return mem;
    }

    void Allocator::free(void* ptr) {
		MemoryBlock block = _memMetrics.RecordDeallocation(ptr);
		::operator delete(ptr, std::align_val_t(block.alignment));
    }

	void Allocator::CheckMemoryLeaks()
	{
		_memMetrics.CheckMemoryLeaks();
	}

	usize Allocator::GetTotalAllocated() { return _memMetrics.totalAllocated; }
	usize Allocator::GetTotalFreed() { return _memMetrics.totalFreed; }
	usize Allocator::GetCurrentUsage() { return _memMetrics.GetCurrentUsage(); }
}