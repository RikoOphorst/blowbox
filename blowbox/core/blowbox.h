#pragma once

namespace blowbox
{
	namespace direct3d
	{
		class Renderer;
	}
	
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
	private:
		bool can_run_; //<! Can the application be run?
		bool running_; //<! Is the application running?
		direct3d::Renderer* renderer_; //<! The renderer this Blowbox uses
	};
}