#pragma once

#include <WindowsIncludes.h>
#include "../../core/memory/memory_object.h"
#include "../../core/input/key.h"
#include "../../core/input/mouse.h"
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
		/**
		* @struct blowbox::InputManager::KeyEvent
		* @author Riko Ophorst
		* @brief Describes an event involving a key
		*/
		struct KeyEvent
		{
			/**
			* @enum blowbox::InputManager::KeyEvent::BB_KEY_EVENT_TYPE
			* @author Riko Ophorst
			* @brief Enumerates all possible event types that involve keys
			*/
			enum BB_KEY_EVENT_TYPE
			{
				BB_KEY_EVENT_UP,
				BB_KEY_EVENT_DOWN
			};

			BB_KEY_TYPE key; //!< The key this event is about
			BB_KEY_EVENT_TYPE event_type; //!< The type of event this key-event is about
		};

		/**
		* @struct blowbox::InputManager::MouseEvent
		* @author Riko Ophorst
		* @brief Describes an event involving the mouse
		*/
		struct MouseEvent
		{
			/**
			* @enum blowbox::InputManager::KeyEvent::BB_KEY_EVENT_TYPE
			* @author Riko Ophorst
			* @brief Enumerates all possible event types that involve the mouse
			*/
			enum BB_MOUSE_EVENT_TYPE
			{
				BB_MOUSE_EVENT_DOWN,
				BB_MOUSE_EVENT_UP,
				BB_MOUSE_EVENT_DBL,
				BB_MOUSE_EVENT_MOVE,
				BB_MOUSE_EVENT_WHEEL,
			};

			BB_MOUSE_BUTTON_TYPE mouse_button; //!< The mouse-button this event is about
			BB_MOUSE_EVENT_TYPE event_type; //!< The type of event this mouse-event is about
			WPARAM wparam; //!< WPARAM accompanying the event
			LPARAM lparam; //!< LPARAM accompanying the event
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

		/**
		* @brief Get the text that was inputted last frame as a nice, displayable string of text
		*/
		const std::string& GetParsedFrameText();

		/**
		* @brief Get the state of a given mouse button
		* @param[in]	mouse_button	The mouse button you want the state of
		*/
		const MouseButtonState& GetMouseButtonState(const BB_MOUSE_BUTTON_TYPE& mouse_button);

		/**
		* @brief Get the state of the mouse (i.e. position, wheel)
		*/
		const MouseState& GetMouseState();
	private:
		static InputManager* instance_; //!< Singleton instance of InputManager

		Window* input_window_; //!< Main window the input manager uses to pull input from
		
		std::map<BB_KEY_TYPE, KeyState> key_states_; //!< The state of every key
		std::queue<KeyEvent> key_events_; //!< All key events get queued up each frame in this container
		std::string parsed_frame_text_; //!< Stores the parsed frame text

		std::map<BB_MOUSE_BUTTON_TYPE, MouseButtonState> mouse_button_states_; //!< The state of every mouse button
		MouseState mouse_state_; //!< The state of the mouse (i.e. position & wheel)
		std::queue<MouseEvent> mouse_events_;

		bool caps_lock_; //!< Is caps lock on?
	};
}