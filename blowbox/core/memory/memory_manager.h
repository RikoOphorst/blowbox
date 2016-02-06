#pragma once

#define BB_MEMORY_SIZE 100000000

namespace blowbox
{
	namespace memory
	{
		class MemoryPool;
		
		class MemoryManager
		{
		private:
			MemoryManager(MemoryPool* memory_pool);
			~MemoryManager();
		
		public:
			static MemoryManager* Create();

		private:
			void* memory_pool_;
		};
	}
}