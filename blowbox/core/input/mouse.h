#pragma once

#include <DirectXMath.h>

using namespace DirectX;

namespace blowbox
{
	/**
	* @enum blowbox::BB_MOUSE_BUTTON_TYPE
	* @author Riko Ophorst
	* @brief Enumerates all mouse button types
	*/
	enum BB_MOUSE_BUTTON_TYPE
	{
		BB_MOUSE_BUTTON_LEFT,
		BB_MOUSE_BUTTON_RIGHT,
		BB_MOUSE_BUTTON_MIDDLE,
		BB_MOUSE_BUTTON_NULL
	};

	/**
	* @struct blowbox::MouseButtonState
	* @author Riko Ophorst
	* @brief The state of a mouse button
	*/
	struct MouseButtonState
	{
		/**
		* @brief MouseButtonState constructor
		*/
		MouseButtonState() : mouse_button(BB_MOUSE_BUTTON_NULL), is_pressed(false), is_released(false), is_down(false) {};
		BB_MOUSE_BUTTON_TYPE mouse_button; //<! The mouse button this MouseButtonState represents
		bool is_pressed; //<! If the mouse button is down, this will be true for one frame and then return to false, even if the mouse button is continued to be held down after the first registered press-frame
		bool is_released; //<! If the mouse button returns to the up-state, this will be true for one frame and then return to false
		bool is_down; //<! Is the mouse button down?
		bool is_dbl; //<! Is the button double clicked?
	};

	/**
	* @struct blowbox::MouseState
	* @author Riko Ophorst
	* @brief The encapsulating state of the mouse
	*/
	struct MouseState
	{
		/**
		* @brief MouseState constructor
		*/
		MouseState() : mouse_position(0.0f, 0.0f), delta_mouse_position(0.0f, 0.0f), delta_wheel(0.0f) {};
		XMFLOAT2 mouse_position; //!< The position of the mouse on the window
		XMFLOAT2 delta_mouse_position; //!< The delta position of the mouse on the window
		float delta_wheel; //!< The position of the wheel on the mouse
	};
}