#pragma once

#include <vector>

#include "../core/memory/memory_object.h"

using namespace blowbox::memory;

namespace blowbox
{
	class Console;
	class Window;
	class Renderer;
	
	/**
	* @class blowbox::Blowbox
	* @author Riko Ophorst
	* @brief Creates a blowbox application
	*/
	class Blowbox : public memory::MObject
	{
	public:
		/**
		* @brief Default blowbox constructor
		*/
		Blowbox(memory::Allocator* allocator);

		/**
		* @brief Default blowbox destructor
		*/
		~Blowbox();

		/**
		* @brief Creates a blowbox instance
		*/
		static Blowbox* Create();

		/**
		* @brief Initialises the blowbox engine
		*/
		void Initialise();

		/**
		* @brief Shuts down the blowbox engine
		*/
		void Shutdown();

		/**
		* @brief Run the blowbox engine
		*/
		void Run();

		/**
		* @brief Set the Window used by blowbox
		* @param[in] window (blowbox::Window*) the window 
		*/
		void SetWindow(Window* window);
	private:
		static bool blowbox_created_; //<! Defines whether an instance of blowbox has been created

		StackAllocator* subsystem_allocator_; //<! Allocator used for allocating subsystems (e.g. renderer, console)
		bool can_run_; //<! Can the application be run?
		bool running_; //<! Is the application running?
		Console* console_; //<! The console this blowbox instance uses
		Window* window_; //<! The window this blowbox instance uses
		Renderer* renderer_; //<! The renderer this blowbox instance uses
	};
}