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
			static MemoryManager* Instance();
		private:
			void* memory_pool_;

			static MemoryManager* instance_;
		};
	}
}