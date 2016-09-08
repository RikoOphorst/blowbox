#pragma once

#include "../core/memory/memory_object.h"

#include <chrono>
#include <deque>

using namespace blowbox::memory;

namespace blowbox
{
	/**
	* @class blowbox::GameTime
	* @author Riko Ophorst
	* @brief Manages time in the game
	*/
	class GameTime : public MObject
	{
	public:
		typedef std::chrono::time_point<std::chrono::system_clock> time_point;

		/**
		* @brief Creates the GameTime instance
		* @param[in]	allocator	The allocator to be used to allocate the instance
		*/
		static GameTime* Create(Allocator* allocator);

		/**
		* @brief Gets the GameTime instance
		*/
		static GameTime* Instance();

		/**
		* @brief GameTime constructor
		* @param[in]	allocator	Allocator used to allocate this instance
		*/
		GameTime(Allocator* allocator);

		/**
		* @brief GameTime destructor
		*/
		~GameTime();

		/**
		* @brief Resets the timer to dummy starting values
		*/
		void Reset();

		/**
		* @brief Ticks (advances) the timer in time. Call this every frame once.
		*/
		void Tick();

		/**
		* @brief Get the current delta time
		*/
		static float GetDelta();

		/**
		* @brief Get the elapsed time since timer start
		*/
		static float GetElapsed();

		/**
		* @brief Get the average delta time (average FPS)
		*/
		static float GetAverageDelta();

		/**
		* @brief Get the number of ticks since timer start
		*/
		static uint64_t GetNumTicks();
	private:
		static GameTime* instance_; //!< Singleton instance of GameTime

		time_point last_frame_time_; //!< The date(time) of the last frame
		float delta_time_; //!< Delta frame time in seconds
		float elapsed_time_; //!< Time since Reset() call (i.e. game start most of the times)
		uint64_t num_ticks_; //!< The number of ticks since timer start

		std::deque<float> delta_times_; //!< Stores [average_delta_precision_] amount of delta times
		float average_delta_precision_; //!< Defines how precise the average FPS/delta calculation should be
	};
}