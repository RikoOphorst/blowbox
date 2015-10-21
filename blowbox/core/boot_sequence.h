#pragma once

namespace blowbox
{
	/**
	* @class blowbox::BootManager
	* @author Riko Ophorst
	* @brief The boot and shutdown sequence of the program is managed by the BootManager
	*/
	class BootSequence
	{
	public:
		BootSequence(); //<! Default BootSequence constructor
		~BootSequence(); //<! Default BootSequence destructor

		/**
		* @brief Boots up all subsystems in the right order in the engine
		*/
		void Boot();

		/**
		* @brief Shuts down all the subsystems in the right order in the engine
		*/
		void ShutDown();
	};
}