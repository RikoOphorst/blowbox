#pragma once

#include <Windows.h>
#include <string>

namespace blowbox
{
	/**
	* @brief A window that can be used for rendering
	* @author Riko Ophorst
	* @class blowbox::Window
	*/
	class Window
	{
	public:
		/**
		* @brief Default Window constructor
		*/
		Window(const std::string& name, unsigned int width_, unsigned int height_);

		/**
		* @brief Default Window destructor
		*/
		~Window();

		/**
		* @brief Reads windows messages
		*/
		static LRESULT CALLBACK WindowProc(HWND hwindow, UINT message, WPARAM wparam, LPARAM lparam);

		/**
		* @brief Reads the windows message queue
		*/
		void ProcessMessages();
	private:
		HWND hwindow_; //<! Handle to the window
		HINSTANCE hinstance_; //<! Windows process handle
		unsigned int width_; //<! Width of the window
		unsigned int height_; //<! Height of the window
		unsigned int aspect_ratio_; //<! Aspect ratio of the window

	};
}