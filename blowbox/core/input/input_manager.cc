#include "input_manager.h"

#include <ctype.h>

#include "../../window/window.h"
#include "../../core/console/console.h"
#include <windowsx.h>

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

		for (int i = 0; i < 5; i++)
		{
			MouseButtonState state = MouseButtonState();
			state.mouse_button = static_cast<BB_MOUSE_BUTTON_TYPE>(i);
			mouse_button_states_.emplace(static_cast<BB_MOUSE_BUTTON_TYPE>(i), state);
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
			/**
			* Keyboard events
			*/
		case WM_KEYDOWN:
			key_events_.push({ static_cast<BB_KEY_TYPE>(message.wParam), KeyEvent::BB_KEY_EVENT_DOWN });
			break;
		case WM_KEYUP:
			key_events_.push({ static_cast<BB_KEY_TYPE>(message.wParam), KeyEvent::BB_KEY_EVENT_UP });
			break;
			/**
			* Mouse events
			*/
		case WM_LBUTTONDOWN:
			mouse_events_.push({ BB_MOUSE_BUTTON_LEFT, MouseEvent::BB_MOUSE_EVENT_DOWN, message.wParam, message.lParam });
			break;
		case WM_LBUTTONUP:
			mouse_events_.push({ BB_MOUSE_BUTTON_LEFT, MouseEvent::BB_MOUSE_EVENT_UP, message.wParam, message.lParam });
			break;
		case WM_LBUTTONDBLCLK:
			mouse_events_.push({ BB_MOUSE_BUTTON_LEFT, MouseEvent::BB_MOUSE_EVENT_DBL, message.wParam, message.lParam });
			break;
		case WM_RBUTTONDOWN:
			mouse_events_.push({ BB_MOUSE_BUTTON_RIGHT, MouseEvent::BB_MOUSE_EVENT_DOWN, message.wParam, message.lParam });
			break;
		case WM_RBUTTONUP:
			mouse_events_.push({ BB_MOUSE_BUTTON_RIGHT, MouseEvent::BB_MOUSE_EVENT_UP, message.wParam, message.lParam });
			break;
		case WM_RBUTTONDBLCLK:
			mouse_events_.push({ BB_MOUSE_BUTTON_RIGHT, MouseEvent::BB_MOUSE_EVENT_DBL, message.wParam, message.lParam });
			break;
		case WM_MBUTTONDOWN:
			mouse_events_.push({ BB_MOUSE_BUTTON_MIDDLE, MouseEvent::BB_MOUSE_EVENT_DOWN, message.wParam, message.lParam });
			break;
		case WM_MBUTTONUP:
			mouse_events_.push({ BB_MOUSE_BUTTON_MIDDLE, MouseEvent::BB_MOUSE_EVENT_UP, message.wParam, message.lParam });
			break;
		case WM_MBUTTONDBLCLK:
			mouse_events_.push({ BB_MOUSE_BUTTON_MIDDLE, MouseEvent::BB_MOUSE_EVENT_DBL, message.wParam, message.lParam });
			break;
		case WM_MOUSEMOVE:
			mouse_events_.push({ BB_MOUSE_BUTTON_NULL, MouseEvent::BB_MOUSE_EVENT_MOVE, message.wParam, message.lParam });
			break;
		case WM_MOUSEWHEEL:
			mouse_events_.push({ BB_MOUSE_BUTTON_NULL, MouseEvent::BB_MOUSE_EVENT_WHEEL, message.wParam, message.lParam });
			break;
		}
	}
	
	//------------------------------------------------------------------------------------------------------
	void InputManager::Update()
	{
		// Reset parsed frame text
		parsed_frame_text_ = "";

		// Check if caps lock is on or off
		caps_lock_ = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0);

		// Reset all the pressed / released states
		for (auto it = key_states_.begin(); it != key_states_.end(); it++)
		{
			it->second.is_pressed = false;
			it->second.is_released = false;
		}

		for (auto it = mouse_button_states_.begin(); it != mouse_button_states_.end(); it++)
		{
			it->second.is_pressed = false;
			it->second.is_released = false;
			it->second.is_dbl = false;
		}

		mouse_state_.delta_mouse_position.x = 0.0f;
		mouse_state_.delta_mouse_position.y = 0.0f;
		mouse_state_.delta_wheel = 0.0f;

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

		while (!mouse_events_.empty())
		{
			MouseEvent& mouse_event = mouse_events_.front();

			switch (mouse_event.event_type)
			{
			case MouseEvent::BB_MOUSE_EVENT_DOWN:
				{
					MouseButtonState& mouse_button_state = mouse_button_states_[mouse_event.mouse_button];

					if (!mouse_button_state.is_down)
					{
						mouse_button_state.is_pressed = true;
					}

					mouse_button_state.is_down = true;
				}
				break;
			case MouseEvent::BB_MOUSE_EVENT_UP:
				{
					MouseButtonState& mouse_button_state = mouse_button_states_[mouse_event.mouse_button];

					if (mouse_button_state.is_down)
					{
						mouse_button_state.is_released = true;
					}

					mouse_button_state.is_down = false;
				}
				break;
			case MouseEvent::BB_MOUSE_EVENT_DBL:
				{
					MouseButtonState& mouse_button_state = mouse_button_states_[mouse_event.mouse_button];

					mouse_button_state.is_dbl = true;
				}
				break;
			case MouseEvent::BB_MOUSE_EVENT_MOVE:
				{
					input_window_->GetWindowHandle();

					XMFLOAT2 new_mouse_position = XMFLOAT2(static_cast<float>(GET_X_LPARAM(mouse_event.lparam)), static_cast<float>(GET_Y_LPARAM(mouse_event.lparam)));

					mouse_state_.delta_mouse_position.x = new_mouse_position.x - mouse_state_.mouse_position.x;
					mouse_state_.delta_mouse_position.y = new_mouse_position.y - mouse_state_.mouse_position.y;

					mouse_state_.mouse_position = new_mouse_position;
				}
				break;
			case MouseEvent::BB_MOUSE_EVENT_WHEEL:
				{
					mouse_state_.delta_wheel = static_cast<float>(GET_WHEEL_DELTA_WPARAM(mouse_event.wparam));
				}
				break;
			}

			mouse_events_.pop();
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
	
	//------------------------------------------------------------------------------------------------------
	const MouseButtonState& InputManager::GetMouseButtonState(const BB_MOUSE_BUTTON_TYPE& mouse_button)
	{
		return mouse_button_states_[mouse_button];
	}
	
	//------------------------------------------------------------------------------------------------------
	const MouseState& InputManager::GetMouseState()
	{
		return mouse_state_;
	}
}