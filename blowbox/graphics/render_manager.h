#pragma once

#include "../../blowbox/memory/memory.h"

namespace blowbox
{
	/**
	* @brief Manages all the rendering
	* @class blowbox::RenderManager
	* @author Riko Ophorst
	*/
	class RenderManager
	{
	public:
		/**
		* @brief Default RenderManager constructor
		*/
		RenderManager();

		/**
		* @brief Default RenderManager destructor
		*/
		~RenderManager();

		/**
		* @brief Retrieve the singleton instance of the RenderManager
		*/
		static RenderManager* Instance();

		/**
		* @brief Starts the render manager up
		*/
		void StartUp();

		/**
		* @brief Shuts the render manager down
		*/
		void ShutDown();
	};
}