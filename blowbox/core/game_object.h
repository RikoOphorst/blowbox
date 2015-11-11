#pragma once

#include "../graphics/direct3d/vertex.h"
#include "../graphics/direct3d/vertex_buffer.h"
#include "../graphics/direct3d/shader.h"

using namespace blowbox::direct3d;

namespace blowbox
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();
		
		const XMFLOAT3& GetPosition();
		VertexBuffer* GetVertexBuffer();
		Shader* GetShader();
	private:

		VertexBuffer* vertex_buffer_;
		Shader* shader_;
	};
}