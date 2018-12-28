#pragma once
#include "../common/common.h"
#include <string>
#include "manager/shader_manager.h"
class Shader
{
	std::string name;
public:
	HRESULT load_shader(const std::string& key, const WCHAR* vertex_path, const WCHAR* pixel_path,
		ComPtr<ID3DBlob>& v_blob, ComPtr<ID3DBlob>& p_blob)
	{
		name = key;
		return ShaderManager::getinstance()->load_shader(key, vertex_path, pixel_path, v_blob, p_blob);
	}
	void set_shader()
	{
		ShaderManager::getinstance()->set_shader(name);
	}
};