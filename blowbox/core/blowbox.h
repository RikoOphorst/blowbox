#pragma once

#include <vector>

namespace blowbox
{
	namespace direct3d
	{
		class Renderer;
	}

	class Window;
	class GameObject;
	
	/**
	* @class blowbox::Blowbox
	* @author Riko Ophorst
	* @brief Creates a blowbox application
	*/
	class Blowbox
	{
	public:
		/**
		* @brief Default blowbox constructor
		*/
		Blowbox();

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
		* @brief Set the Renderer used by blowbox
		* @param[in] renderer (blowbox::direct3d::Renderer*) The renderer
		*/
		void SetRenderer(direct3d::Renderer* renderer);

		/**
		* @brief Set the Window used by blowbox
		* @param[in] window (blowbox::Window*) the window 
		*/
		void SetWindow(Window* window);

		void AddGameObject(GameObject* game_object);
	private:
		bool can_run_; //<! Can the application be run?
		bool running_; //<! Is the application running?
		direct3d::Renderer* renderer_; //<! The renderer this Blowbox uses
		Window* window_; //<! The window this Blowbox uses
		std::vector<GameObject*> game_objects_; //<! All the game objects in the game
	};
}