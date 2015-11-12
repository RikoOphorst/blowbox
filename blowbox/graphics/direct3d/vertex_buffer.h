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
		* @brief A VertexBuffer is a DirectX 12 resource that is created from a set of vertices
		*/
		class VertexBuffer
		{
		public:
			/**
			* @brief Default constructor
			* @param[in] verts (const std::vector<Vertex>&) the vertices of this VertexBuffer
			* @param[in] topology (const D3D12_PRIMITIVE_TOPOLOGY&) the topology of the vertices in the buffer
			* @param[in] device (ID3D12Device*) the device the vertex buffer belongs to
			*/
			VertexBuffer(const std::vector<Vertex>& verts, const D3D12_PRIMITIVE_TOPOLOGY& topology, ID3D12Device* device);

			/**
			* @brief Default destructor
			*/
			~VertexBuffer();

			/**
			* @brief Creates an instance of this class
			* @param[in] verts (const std::vector<Vertex>&) the vertices of this VertexBuffer
			* @param[in] topology (const D3D12_PRIMITIVE_TOPOLOGY&) the topology of the vertices in the buffer
			* @param[in] device (Device*) the device the vertex buffer belongs to
			*/
			static VertexBuffer* Create(const std::vector<Vertex>& verts, const D3D12_PRIMITIVE_TOPOLOGY& topology, Device* device);

			/**
			* @brief Get the actual vertex buffer
			*/
			ID3D12Resource* GetVertexBuffer() const;

			/**
			* @brief Get the vertex buffer view
			*/
			const D3D12_VERTEX_BUFFER_VIEW& GetVertexView() const;

			/**
			* @brief Get the vertices in the buffer
			*/
			const std::vector<Vertex>& GetVertices() const;

			/**
			* @brief Get the topology of the vertices
			*/
			const D3D12_PRIMITIVE_TOPOLOGY& GetTopology() const;
		private:
			ID3D12Resource* vert_buffer_; //<! The actual vertex buffer
			D3D12_VERTEX_BUFFER_VIEW vert_buffer_view_; //<! The vertex buffer view
			std::vector<Vertex> verts_; //<! The vertices in the buffer
			D3D12_PRIMITIVE_TOPOLOGY topology_; //<! The topology of the vertices
		};
	}
}