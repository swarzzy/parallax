#pragma once

namespace prx::internal {
	class MemoryManager {
		PRX_DISALLOW_COPY_AND_MOVE(MemoryManager)
	private:
		inline static size_t s_TotalMemoryUsed = 0;

	public:
		MemoryManager() = delete;

		inline static void registerAlloc(const size_t& size) {
			s_TotalMemoryUsed += size;
		}

		inline static void registerFree(size_t size) {
			s_TotalMemoryUsed -= size;
		}

		inline static size_t getUsage() {
			return s_TotalMemoryUsed;
		}

		inline static float getUsageMb() {
			return s_TotalMemoryUsed / 1024.0f / 1024.0f;
		}
	};
}
