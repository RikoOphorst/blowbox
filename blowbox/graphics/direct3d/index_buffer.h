#pragma once

namespace blowbox
{
	namespace direct3d
	{
		/**
		* @class blowbox::direct3d::IndexBuffer
		* @author Riko Ophorst
		* @brief Bla bla bla
		*/
		class IndexBuffer
		{
		public:
			/**
			* @brief Default constructor
			*/
			IndexBuffer();

			/**
			* @brief Default destructor
			*/
			~IndexBuffer();

			/**
			* @brief Creates an instance of this class
			*/
			static IndexBuffer* Create();
		};
	}
}