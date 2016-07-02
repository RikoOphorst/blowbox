#pragma once

#include <vector>

#include "../core/memory/memory_object.h"

namespace blowbox
{
	class Window;
	class GameObject;
	
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
		static Blowbox* Create(memory::Allocator* allocator);

		/**
		* @brief Initialises the blowbox engine
		*/
		void Initialise();

		/**
		* @brief Run the blowbox engine
		*/
		void Run();

		/**
		* @brief Set the Window used by blowbox
		* @param[in] window (blowbox::Window*) the window 
		*/
		void SetWindow(Window* window);

		void AddGameObject(GameObject* game_object);
	private:
		bool can_run_; //<! Can the application be run?
		bool running_; //<! Is the application running?
		Window* window_; //<! The window this Blowbox uses
		std::vector<GameObject*> game_objects_; //<! All the game objects in the game
	};
}