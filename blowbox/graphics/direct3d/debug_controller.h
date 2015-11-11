#pragma once

namespace blowbox
{
	namespace direct3d
	{
		/**
		* @class blowbox::direct3d::DebugController
		* @author Riko Ophorst
		* @brief Bla bla bla
		*/
		class DebugController
		{
		public:
			/**
			* @brief Default constructor
			*/
			DebugController();

			/**
			* @brief Default destructor
			*/
			~DebugController();

			/**
			* @brief Creates an instance of this class
			*/
			static DebugController* Create();
		};
	}
}