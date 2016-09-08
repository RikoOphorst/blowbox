#include "game_time.h"

namespace blowbox
{
	GameTime* GameTime::instance_ = nullptr;

	//------------------------------------------------------------------------------------------------------
	GameTime* GameTime::Create(Allocator* allocator)
	{
		return instance_ = memory::MemoryManager::Allocate<GameTime>(allocator, allocator);
	}

	//------------------------------------------------------------------------------------------------------
	GameTime* GameTime::Instance()
	{
		return instance_;
	}

	//------------------------------------------------------------------------------------------------------
	GameTime::GameTime(Allocator* allocator) :
		MObject(allocator),
		delta_time_(0.0f),
		elapsed_time_(0.0f),
		average_delta_precision_(100)
	{

	}

	//------------------------------------------------------------------------------------------------------
	GameTime::~GameTime()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void GameTime::Reset()
	{
		last_frame_time_ = std::chrono::high_resolution_clock::now();
		elapsed_time_ = 0.0f;
		delta_time_ = 0.0f;
		delta_times_.clear();
	}

	//------------------------------------------------------------------------------------------------------
	void GameTime::Tick()
	{
		time_point now = std::chrono::high_resolution_clock::now();
		
		delta_time_ = static_cast<float>((std::chrono::duration_cast<std::chrono::microseconds>(now - last_frame_time_)).count()) / 1000000.0f;
		elapsed_time_ += delta_time_;

		delta_times_.push_front(delta_time_);
		if (delta_times_.size() >= average_delta_precision_)
		{
			delta_times_.pop_back();
		}

		last_frame_time_ = now;
	}
	
	//------------------------------------------------------------------------------------------------------
	float GameTime::GetDelta()
	{
		return Instance()->delta_time_;
	}
	
	//------------------------------------------------------------------------------------------------------
	float GameTime::GetElapsed()
	{
		return Instance()->elapsed_time_;
	}

	//------------------------------------------------------------------------------------------------------
	float GameTime::GetAverageDelta()
	{
		GameTime* g = Instance();

		float total = 0.0f;
		for (auto it = g->delta_times_.begin(); it != g->delta_times_.end(); it++)
		{
			total += *it;
		}

		return total / g->delta_times_.size();
	}
}