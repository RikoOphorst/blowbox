#pragma once

#include "../../core/memory/memory_object.h"
#include <WindowsIncludes.h>

using namespace blowbox::memory;

namespace blowbox
{
	class Window;

	/**
	* @class blowbox::InputManager
	* @author Riko Ophorst
	* @brief Manages input from the user and makes it easily accessible
	*/
	class InputManager : public MObject
	{
	public:
		/**
		* @brief Create the instance of the input manager
		* @param[in]	allocator		The allocator to use to allocate this manager
		* @param[in]	input_window	Window that should be used as "input provider"
		*/
		static InputManager* Create(Allocator* allocator, Window* input_window);

		/**
		* @brief Singleton accessor to the instance of this InputManager
		*/
		static InputManager* Instance();

		/**
		* @brief InputManager constructor
		* @param[in]	allocator		The allocator used to allocate this manager
		* @param[in]	input_window	Window that should be used as "input provider"
		*/
		InputManager(Allocator* allocator, Window* input_window);

		/**
		* @brief InputManager destructor
		*/
		~InputManager();

		/**
		* @brief Processes input from the Windows message queue
		* @param[in]	message		The message to be processed
		*/
		void ProcessWinMessage(MSG message);
	private:
		Window* input_window_; //!< Main window the input manager uses to pull input from
		static InputManager* instance_; //!< Singleton instance of InputManager
	};
}