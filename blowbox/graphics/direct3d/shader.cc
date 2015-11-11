#include "shader.h"

#include "../../util/s2ws.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		Shader::Shader(const std::string& path, const BB_SHADER_TYPES& type) :
			pixel_shader_(nullptr),
			vertex_shader_(nullptr),
			domain_shader_(nullptr),
			hull_shader_(nullptr),
			geometry_shader_(nullptr),
			error_blob_(nullptr)
		{
			if (type & BB_SHADER_TYPES::BB_SHADER_TYPE_PIXEL_SHADER)
			{
				CompileShader(path, "PSMain", "ps_5_0", &pixel_shader_);
			}

			if (type & BB_SHADER_TYPES::BB_SHADER_TYPE_VERTEX_SHADER)
			{
				CompileShader(path, "VSMain", "vs_5_0", &vertex_shader_);
			}

			if (type & BB_SHADER_TYPES::BB_SHADER_TYPE_DOMAIN_SHADER)
			{
				CompileShader(path, "DSMain", "ds_5_0", &domain_shader_);
			}

			if (type & BB_SHADER_TYPES::BB_SHADER_TYPE_HULL_SHADER)
			{
				CompileShader(path, "HSMain", "hs_5_0", &hull_shader_);
			}

			if (type & BB_SHADER_TYPES::BB_SHADER_TYPE_GEOMETRY_SHADER)
			{
				CompileShader(path, "GSMain", "gs_5_0", &geometry_shader_);
			}
		}

		//------------------------------------------------------------------------------------------------------
		Shader::~Shader()
		{
			BB_SAFE_RELEASE(pixel_shader_);
			BB_SAFE_RELEASE(vertex_shader_);
			BB_SAFE_RELEASE(domain_shader_);
			BB_SAFE_RELEASE(hull_shader_);
			BB_SAFE_RELEASE(geometry_shader_);
			BB_SAFE_RELEASE(error_blob_);
		}

		//------------------------------------------------------------------------------------------------------
		Shader* Shader::Create(const std::string& path, const BB_SHADER_TYPES& type)
		{
			return new Shader(path, type);
		}

		//------------------------------------------------------------------------------------------------------
		D3D12_SHADER_BYTECODE Shader::GetPixelShader()
		{
			return{ reinterpret_cast<UINT8*>(pixel_shader_->GetBufferPointer()), pixel_shader_->GetBufferSize() };
		}

		//------------------------------------------------------------------------------------------------------
		D3D12_SHADER_BYTECODE Shader::GetVertexShader()
		{
			return{ reinterpret_cast<UINT8*>(vertex_shader_->GetBufferPointer()), vertex_shader_->GetBufferSize() };
		}

		//------------------------------------------------------------------------------------------------------
		D3D12_SHADER_BYTECODE Shader::GetHullShader()
		{
			return{ reinterpret_cast<UINT8*>(hull_shader_->GetBufferPointer()), hull_shader_->GetBufferSize() };
		}

		//------------------------------------------------------------------------------------------------------
		D3D12_SHADER_BYTECODE Shader::GetGeometryShader()
		{
			return{ reinterpret_cast<UINT8*>(geometry_shader_->GetBufferPointer()), geometry_shader_->GetBufferSize() };
		}

		//------------------------------------------------------------------------------------------------------
		D3D12_SHADER_BYTECODE Shader::GetDomainShader()
		{
			return{ reinterpret_cast<UINT8*>(domain_shader_->GetBufferPointer()), domain_shader_->GetBufferSize() };
		}
		
		//------------------------------------------------------------------------------------------------------
		void Shader::CompileShader(const std::string& path, const std::string& func, const std::string& target, ID3DBlob** blob)
		{
#ifdef _DEBUG
			UINT compile_flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
			UINT compile_flags = 0;
#endif
			
			D3DCompileFromFile(util::s2ws(path).c_str(), nullptr, nullptr, func.c_str(), target.c_str(), compile_flags, 0, blob, &error_blob_);

			if (error_blob_ != nullptr)
			{
				BB_REPORT(static_cast<char*>(error_blob_->GetBufferPointer()));
				error_blob_->Release();
			}
		}
	}
}