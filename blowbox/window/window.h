#pragma once

#include <WindowsIncludes.h>
#include <string>
#include <functional>

#include "../core/memory/memory_object.h"
#include "../core/input/input_manager.h"

namespace blowbox
{
	/**
	* @class blowbox::Window
	* @author Riko Ophorst
	* @brief A window that can be used for rendering
	*/
	class Window : public memory::MObject
	{
	public:
		/**
		* @brief Factory method for creating a window
		* @param[in]	allocator	The allocator that should be used to create this window
		* @param[in]	name		The name of the window (the title)
		* @param[in]	width		The width of the inner window
		* @param[in]	height		The height of the inner window
		*/
		static Window* Create(memory::Allocator* allocator, const std::string& name, unsigned int width, unsigned int height);
		
		/**
		* @brief Window constructor
		* @param[in]	allocator	The allocator that's used to create this window
		* @param[in]	name		The name of the window (the title)
		* @param[in]	width		The width of the inner window
		* @param[in]	height		The height of the inner window
		*/
		Window(memory::Allocator* allocator, const std::string& name, unsigned int width, unsigned int height);

		~Window(); //!< Window destructor

		/**
		* @brief Reads windows messages
		* @param[in]	hwindow		Handle to the window
		* @param[in]	message		The received message
		* @param[in]	wparam		WPARAM component of the message
		* @param[in]	lparam		LPARAM component of the message
		*/
		static LRESULT CALLBACK WindowProc(HWND hwindow, UINT message, WPARAM wparam, LPARAM lparam);

		void ProcessMessages(); //!< Processes the message queue

		const HWND& GetWindowHandle() const; //!< Get the window handle
		const HINSTANCE& GetWindowInstance() const; //!< Get the window instance
		const unsigned int& GetWidth() const; //!< Get the width of the window
		const unsigned int& GetHeight() const; //!< Get the height of the window
		const float& GetAspectRatio() const; //!< Get the aspect ratio of the window
		
		/**
		* @brief Sets the function that should be called when a message arrives in the message queue of the window
		* @param[in]	listener	The listener function
		*/
		void SetWindowInputListener(std::function<void(MSG message)> listener);

		/**
		* @brief Set on window quit listener
		* @param[in]	listener	The listener function
		*/
		void SetWindowQuitListener(std::function<void(void)> listener);
	private:
		HWND hwindow_; //!< Handle to the window
		HINSTANCE hinstance_; //!< Windows process handle
		unsigned int width_; //!< Width of the window
		unsigned int height_; //!< Height of the window
		float aspect_ratio_; //!< Aspect ratio of the window
		std::function<void(MSG message)> window_input_listener_; //!< Listener to the input of the window
		std::function<void(void)> window_quit_listener_; //!< Listener to the window quit message
	};
}