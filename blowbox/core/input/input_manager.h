#pragma once

#include <WindowsIncludes.h>
#include "../../core/memory/memory_object.h"
#include "../../core/input/key.h"
#include <map>
#include <queue>

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
		struct KeyEvent
		{
			enum BB_KEY_EVENT_TYPE
			{
				BB_KEY_EVENT_UP,
				BB_KEY_EVENT_DOWN
			};

			BB_KEY_TYPE key;
			BB_KEY_EVENT_TYPE event_type;
		};

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

		/**
		* @brief Updates the input manager
		*/
		void Update();

		/**
		* @brief Get the state of a given key
		* @param[in]	key		The key you want the state of
		*/
		const KeyState& GetKey(const BB_KEY_TYPE& key);

		const std::string& GetParsedFrameText();
	private:
		static InputManager* instance_; //!< Singleton instance of InputManager

		Window* input_window_; //!< Main window the input manager uses to pull input from
		std::map<BB_KEY_TYPE, KeyState> key_states_; //!< The state of every key
		std::queue<KeyEvent> key_events_; //!< All key events get queued up each frame in this container
		std::string parsed_frame_text_; //!< Stores the parsed frame text
		bool caps_lock_; //!< Is caps lock on?
	};
}