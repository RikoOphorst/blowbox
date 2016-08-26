#pragma once

#include <vector>

#include "../core/memory/memory_object.h"

using namespace blowbox::memory;

namespace blowbox
{
	class Console;
	class TaskManager;
	class Window;
	class Renderer;
	class InputManager;

	/**
	* @class blowbox::Blowbox
	* @author Riko Ophorst
	* @brief Creates a blowbox application
	*/
	class Blowbox : public MObject
	{
	public:
		/**
		* @brief Default blowbox constructor
		*/
		Blowbox(Allocator* allocator);

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
		* @brief Run the blowbox engine
		*/
		void Run();

		/**
		* @brief Shuts down the blowbox engine
		*/
		void Shutdown();

		Console* GetConsole() const; //<! Get the console
		Window* GetWindow() const; //<! Get the window
		Renderer* GetRenderer() const; //<! Get the renderer
		InputManager* GetInputManager() const; //<! Get the input manager
	private:
		static bool blowbox_created_; //<! Defines whether an instance of blowbox has been created

		StackAllocator* subsystem_allocator_; //<! Allocator used for allocating subsystems (e.g. renderer, console)
		bool can_run_; //<! Can the application be run?
		bool running_; //<! Is the application running?
		Console* console_; //<! The console this blowbox instance uses
		TaskManager* task_manager_; //<! The task manager this blowbox instance uses
		Window* window_; //<! The window this blowbox instance uses
		Renderer* renderer_; //<! The renderer this blowbox instance uses
		InputManager* input_manager_; //<! The input manager this blowbox instance uses
	};
}