#pragma once

namespace blowbox
{
	namespace memory
	{
		class Allocator
		{
		private:
			Allocator();
			~Allocator();
		public:
			static Allocator* Create();

		private:
			
		};
	}
}