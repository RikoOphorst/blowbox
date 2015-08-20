#pragma once

#include "../../blowbox/memory/memory.h"
#include "../../blowbox/window/window.h"
#include <string>

namespace blowbox
{
	/**
	* @brief Manages all the windows
	* @author Riko Ophorst
	* @class blowbox::WindowManager
	*/
	class WindowManager
	{
	public:
		/**
		* @brief Default WindowManager constructor
		*/
		WindowManager();

		/**
		* @brief Default WindowManager destructor
		*/
		~WindowManager();

		/**
		* @brief Retrieves the WindowManager singleton pointer
		*/
		static WindowManager* Instance();

		/**
		* @brief Starts up the window manager
		*/
		void StartUp();

		/**
		* @brief Shuts down the window manager
		*/
		void ShutDown();

		/**
		* @brief Creates a Window
		*/
		Window* MakeWindow(const std::string& name, unsigned int width, unsigned int height);
	private:
		PoolAllocator* windows_; //<! Holds all windows
	};
}