#pragma once

#include <memory>

namespace blowbox
{
	namespace memory
	{
		/**
		* @class blowbox::memory::Allocator
		* @author Riko Ophorst
		* @brief Allocator base class providing base functionality for allocators
		*/
		class Allocator
		{
		public:
			/**
			* @brief Allocator constructor
			* @param[in]	start	Start of the memory block
			* @param[in]	size	Size of the memory block
			*/
			Allocator(void* start, const size_t& size);

			virtual ~Allocator(); //<! Allocator destructor

			/**
			* @brief Allocates a new block of memory within this allocator
			* @param[in]	size		The size of the memory block we're allocating
			* @param[in]	alignment	The alignment of the memory block we're allocating
			*/
			virtual void* Allocate(const size_t& size, const uint32_t& alignment = 4) = 0;
			
			/**
			* @brief Deallocates a block of memory
			* @param[in]	ptr		Pointer to the memory to be deallocated
			*/
			virtual void Deallocate(void* ptr) = 0;

			void* GetStart(); //<! Get the start of the memory block
			const size_t& GetSize(); //<! Get the size of the memory block

			const size_t& GetUsedMemory(); //<! Get the used memory in this allocator
			const size_t& GetNumAllocations(); //<! Get the number of allocations in the allocator

			void SetHeapInspectorNotifications(const bool& enabled); //<! Set whether this allocator notifies HeapInspector of allocs/deallocs
			const bool& GetHeapInspectorNotifications(); //<! Get whether we're notifying HeapInspector of allocs/deallocs
		protected:
			void* start_; //<! Start of the memory block
			size_t size_; //<! Size of the memory block

			size_t used_memory_; //<! Used memory in the allocator
			size_t num_allocations_; //<! Number of allocations in the allocator

			bool heap_inspector_notifications_enabled_; //<! Are we notifying HeapInspector?
		};
	}
}