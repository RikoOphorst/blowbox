#pragma once

#include "../../graphics/direct3d/direct3d.h"

using namespace DirectX;

namespace blowbox
{
	namespace direct3d
	{
		struct Vertex
		{
			XMFLOAT3 position;
			XMFLOAT4 color;
			XMFLOAT2 uv;
			XMFLOAT3 normal;
		};
	}
}