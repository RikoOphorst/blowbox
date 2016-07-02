#pragma once

#include <WindowsIncludes.h>
#include <string>

namespace blowbox
{
	/**
	* @class blowbox::Window
	* @author Riko Ophorst
	* @brief A window that can be used for rendering
	*/
	class Window
	{
	public:
		/**
		* @brief Factory method for creating a window
		* @param[in] name (const std::string&) the name of the window (the title)
		* @param[in] width (unsigned int) the width of the inner window
		* @param[in] height (unsigned int) the height of the inner window
		*/
		static Window* MakeWindow(const std::string& name, unsigned int width, unsigned int height);
		
		/**
		* @brief Default Window constructor
		* @param[in] name (const std::string&) the name of the window (the title)
		* @param[in] width (unsigned int) the width of the inner window
		* @param[in] height (unsigned int) the height of the inner window
		*/
		Window(const std::string& name, unsigned int width, unsigned int height);

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

		const HWND& GetWindowHandle() const;
		const HINSTANCE& GetWindowInstance() const;
		const unsigned int& GetWidth() const;
		const unsigned int& GetHeight() const;
		const float& GetAspectRatio() const;
	private:
		HWND hwindow_; //<! Handle to the window
		HINSTANCE hinstance_; //<! Windows process handle
		unsigned int width_; //<! Width of the window
		unsigned int height_; //<! Height of the window
		float aspect_ratio_; //<! Aspect ratio of the window
	};
}