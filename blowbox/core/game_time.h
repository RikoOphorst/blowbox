#pragma once

#include "../core/memory/memory_object.h"

#include <chrono>
#include <deque>

using namespace blowbox::memory;

namespace blowbox
{
	class GameTime : public MObject
	{
	public:
		typedef std::chrono::time_point<std::chrono::system_clock> time_point;

		static GameTime* Create(Allocator* allocator);
		static GameTime* Instance();

		GameTime(Allocator* allocator);
		~GameTime();

		void Reset();
		void Tick();

		static float GetDelta();
		static float GetElapsed();
		static float GetAverageDelta();
	private:
		static GameTime* instance_;

		time_point last_frame_time_;
		float delta_time_; //!< Delta frame time in seconds
		float elapsed_time_; //!< Time since Reset() call (i.e. game start most of the times)

		std::deque<float> delta_times_;
		float average_delta_precision_;
	};
}