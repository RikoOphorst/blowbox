#pragma once

namespace blowbox
{
	namespace direct3d
	{
		/**
		* @class blowbox::direct3d::DepthStencil
		* @author Riko Ophorst
		* @brief Bla bla bla
		*/
		class DepthStencil
		{
		public:
			/**
			* @brief Default constructor
			*/
			DepthStencil();

			/**
			* @brief Default destructor
			*/
			~DepthStencil();

			/**
			* @brief Creates an instance of this class
			*/
			static DepthStencil* Create();
		};
	}
}