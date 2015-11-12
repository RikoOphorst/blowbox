#pragma once

#include "../../graphics/direct3d/vertex_buffer.h"

#include <vector>

namespace blowbox
{
	namespace direct3d
	{
		struct Vertex;
		class Device;
		
		/**
		* @class blowbox::direct3d::IndexedVertexBuffer
		* @author Riko Ophorst
		* @brief A vertex buffer with an attached index buffer for improved efficiency
		*/
		class IndexedVertexBuffer : public VertexBuffer
		{
		public:
			/**
			* @brief Default constructor
			* @param[in] vertices (const std::vector<Vertex>&) the vertices of this VertexBuffer
			* @param[in] indices (const std::vector<unsigned int>&) the indices of the IndexBuffer
			* @param[in] topology (const D3D12_PRIMITIVE_TOPOLOGY&) the topology of the vertices in the buffer
			* @param[in] device (ID3D12Device*) the device the vertex buffer belongs to
			*/
			IndexedVertexBuffer(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const D3D12_PRIMITIVE_TOPOLOGY& topology, ID3D12Device* device);
			
			/**
			* @brief Default destructor
			*/
			~IndexedVertexBuffer();

			/**
			* @brief Default constructor
			* @param[in] vertices (const std::vector<Vertex>&) the vertices of this VertexBuffer
			* @param[in] indices (const std::vector<unsigned int>&) the indices of the IndexBuffer
			* @param[in] topology (const D3D12_PRIMITIVE_TOPOLOGY&) the topology of the vertices in the buffer
			* @param[in] device (Device*) the device the vertex buffer belongs to
			*/
			static IndexedVertexBuffer* Create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const D3D12_PRIMITIVE_TOPOLOGY& topology, Device* device);

			/**
			* @brief Get the index buffer
			*/
			ID3D12Resource* GetIndexBuffer() const;

			/**
			* @brief Get the index buffer view
			*/
			const D3D12_INDEX_BUFFER_VIEW& GetIndexView() const;

			/**
			* @brief Get the indices in this buffer
			*/
			const std::vector<unsigned int>& GetIndices() const;
		private:
			ID3D12Resource* index_buffer_; //<! The actual index buffer
			D3D12_INDEX_BUFFER_VIEW index_buffer_view_; //<! The index buffer view
			std::vector<unsigned int> indices_; //<! The indices of this index buffer
		};
	}
}