#pragma once

namespace blowbox
{
	class Window;
	
	namespace direct3d
	{
		/**
		* @class blowbox::direct3d::Renderer
		* @author Riko Ophorst
		* @brief A Direct3D renderer
		*/
		class Renderer
		{
		public:
			/**
			* @brief Factory method for instancing of Renderer object
			*/
			static Renderer* MakeRenderer();

			/**
			* @brief Default Renderer constructor
			*/
			Renderer();

			/**
			* @brief Default Renderer destructor
			*/
			~Renderer();

			/**
			* @brief Set this renderer's window output target
			* @param[in] window (Window*) the window
			*/
			void SetWindow(Window* window);
		private:
			Window* window_; //<! The output window of this renderer
		};
	}
}