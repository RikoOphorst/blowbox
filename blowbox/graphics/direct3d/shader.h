#pragma once

#include "../../graphics/direct3d/direct3d.h"

#include <string>

namespace blowbox
{
	namespace direct3d
	{
		/**
		* @enum blowbox::direct3d::BB_SHADER_TYPES
		* @author Riko Ophorst
		* @brief Defines all types of shaders
		*/
		enum BB_SHADER_TYPES
		{
			BB_SHADER_TYPE_PIXEL_SHADER = 1,
			BB_SHADER_TYPE_VERTEX_SHADER = 2,
			BB_SHADER_TYPE_DOMAIN_SHADER = 4,
			BB_SHADER_TYPE_HULL_SHADER = 8,
			BB_SHADER_TYPE_GEOMETRY_SHADER = 16
		};

		/**
		* @brief Bitwise OR operator, allows multiple types to be flagged in one variable
		*/
		inline BB_SHADER_TYPES operator|(BB_SHADER_TYPES a, BB_SHADER_TYPES b)
		{
			return static_cast<BB_SHADER_TYPES>(static_cast<int>(a) | static_cast<int>(b));
		}

		/**
		* @class blowbox::direct3d::Shader
		* @author Riko Ophorst
		* @brief A shader class that wraps DirectX 12 shaders
		*/
		class Shader
		{
		public:
			/**
			* @brief Default constructor
			* @param[in] path (const std::string&) the path to the shader
			* @param[in] type (const BB_SHADER_TYPES&) the type of shader
			*/
			Shader(const std::string& path, const BB_SHADER_TYPES& type);

			/**
			* @brief Default destructor
			*/
			~Shader();

			/**
			* @brief Creates a shader
			* @param[in] path (const std::string&) the path to the shader
			* @param[in] type (const BB_SHADER_TYPES&) the type of shader
			*/
			static Shader* Create(const std::string& path, const BB_SHADER_TYPES& type);

			D3D12_SHADER_BYTECODE GetPixelShader();
			D3D12_SHADER_BYTECODE GetVertexShader();
			D3D12_SHADER_BYTECODE GetDomainShader();
			D3D12_SHADER_BYTECODE GetHullShader();
			D3D12_SHADER_BYTECODE GetGeometryShader();

		protected:
			/**
			* @brief Compiles a shader and outputs to a specific blob, also handles errors
			* @param[in] path (const std::string&) the path to the path
			* @param[in] func (const std::string&) the main function for the shader (the entry point)
			* @param[in] target (const std::string&) the target of the shader (shader type + shader version, e.g. "ps_5_0")
			* @param[in] blob (ID3DBlob**) the blob the shader should be stored it
			*/
			void CompileShader(const std::string& path, const std::string& func, const std::string& target, ID3DBlob** blob);

		private:
			ID3DBlob* pixel_shader_; //<! The pixel shader
			ID3DBlob* vertex_shader_; //<! The vertex shader
			ID3DBlob* domain_shader_; //<! The domain shader
			ID3DBlob* hull_shader_; //<! The hull shader
			ID3DBlob* geometry_shader_; //<! The geometry shader
			ID3DBlob* error_blob_; //<! Error blob
		};
	}
}