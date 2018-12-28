#pragma once
#include "../../common/common.h"
#include <saki/singleton/singleton.h>
#include <string>
#include <unordered_map>
class Shader;
class ShaderManager :public saki::Singleton<ShaderManager>
{
	friend class Shader;
	struct ComPtrShader
	{
		ComPtr<ID3D11VertexShader> vertex_shader;
		ComPtr<ID3D11PixelShader> pixel_shader;
		ComPtr<ID3D11InputLayout> input_layout;
	};
	std::unordered_map<std::string, ComPtrShader> shader_map;
	HRESULT load_shader(const std::string&, const WCHAR*, const WCHAR*,
		ComPtr<ID3DBlob>&, ComPtr<ID3DBlob>&);
	void set_shader(const std::string&);
};