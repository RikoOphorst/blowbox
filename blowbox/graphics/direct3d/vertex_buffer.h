#pragma once

#include "../../graphics/direct3d/direct3d.h"

#include <vector>

namespace blowbox
{
	namespace direct3d
	{
		struct Vertex;
		class Device;
		
		/**
		* @class blowbox::direct3d::VertexBuffer
		* @author Riko Ophorst
		* @brief Bla bla bla
		*/
		class VertexBuffer
		{
		public:
			/**
			* @brief Default constructor
			*/
			VertexBuffer(const std::vector<Vertex> verts, ID3D12Device* device);

			/**
			* @brief Default destructor
			*/
			~VertexBuffer();

			/**
			* @brief Creates an instance of this class
			*/
			static VertexBuffer* Create(const std::vector<Vertex> verts, Device* device);

			ID3D12Resource* Get();

			const D3D12_VERTEX_BUFFER_VIEW& GetView();
			const std::vector<Vertex>& GetVerts();
		private:
			ID3D12Resource* vert_buffer_;
			D3D12_VERTEX_BUFFER_VIEW vert_buffer_view_;
			std::vector<Vertex> verts_;
			unsigned int vert_size_;
		};
	}
}