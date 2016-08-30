#include "input_manager.h"

#include <ctype.h>

#include "../../window/window.h"
#include "../../core/console/console.h"

using namespace std::placeholders;

namespace blowbox
{
	InputManager* InputManager::instance_ = nullptr;

	//------------------------------------------------------------------------------------------------------
	InputManager* InputManager::Create(Allocator* allocator, Window* input_window)
	{
		return instance_ = MemoryManager::Allocate<InputManager>(allocator, allocator, input_window);
	}

	//------------------------------------------------------------------------------------------------------
	InputManager* InputManager::Instance()
	{
		return instance_;
	}

	//------------------------------------------------------------------------------------------------------
	InputManager::InputManager(Allocator* allocator, Window* input_window) :
		MObject(allocator),
		input_window_(input_window)
	{

		std::function<void(MSG message)> message = std::bind(&InputManager::ProcessWinMessage, this, _1);
		input_window_->SetWindowInputListener(message);

		for (int i = 0; i < 300; i++)
		{
			KeyState state = KeyState();
			state.key = static_cast<BB_KEY_TYPE>(i);
			key_states_.emplace(static_cast<BB_KEY_TYPE>(i), state);
		}
	}

	//------------------------------------------------------------------------------------------------------
	InputManager::~InputManager()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void InputManager::ProcessWinMessage(MSG message)
	{
		switch (message.message)
		{
		case WM_KEYDOWN:
			key_events_.push({ static_cast<BB_KEY_TYPE>(message.wParam), KeyEvent::BB_KEY_EVENT_DOWN });
			break;
		case WM_KEYUP:
			key_events_.push({ static_cast<BB_KEY_TYPE>(message.wParam), KeyEvent::BB_KEY_EVENT_UP });
			break;
		}
	}
	
	//------------------------------------------------------------------------------------------------------
	void InputManager::Update()
	{
		// Reset parsed frame text
		parsed_frame_text_ = "";

		// Check if caps lock is on or off
		caps_lock_ = (GetKeyState(VK_CAPITAL) & 0x0001 != 0);

		// Reset all the pressed / released states
		for (auto it = key_states_.begin(); it != key_states_.end(); it++)
		{
			it->second.is_pressed = false;
			it->second.is_released = false;
		}

		// Process all key events
		while (!key_events_.empty())
		{
			KeyEvent& evt = key_events_.front();

			KeyState& key_state = key_states_[evt.key];

			switch (evt.event_type)
			{
			case KeyEvent::BB_KEY_EVENT_DOWN:
				if (!key_state.is_down)
				{
					key_state.is_pressed = true;
				}
				
				key_state.is_down = true;

				if (IsKeyAChar(evt.key))
				{
					bool shifted = key_states_[BB_KEY_SHIFT].is_down;

					if (caps_lock_)
						shifted = !shifted;

					parsed_frame_text_ += KeyToChar(evt.key, key_states_[BB_KEY_SHIFT].is_down, caps_lock_);
				}
				break;
			case KeyEvent::BB_KEY_EVENT_UP:
				if (key_state.is_down)
				{
					key_state.is_released = true;
				}

				key_state.is_down = false;
				break;
			}

			key_events_.pop();
		}
	}
	
	//------------------------------------------------------------------------------------------------------
	const KeyState& InputManager::GetKey(const BB_KEY_TYPE& key)
	{
		return key_states_[key];
	}
	
	//------------------------------------------------------------------------------------------------------
	const std::string& InputManager::GetParsedFrameText()
	{
		return parsed_frame_text_;
	}
}