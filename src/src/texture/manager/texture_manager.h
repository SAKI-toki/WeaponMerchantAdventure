#pragma once
#include "../../common/common.h"
#include <saki/singleton/singleton.h>
#include <unordered_map>
#include <string>
class Texture;
class TextureManager :public saki::Singleton<TextureManager>
{
	friend class Texture;
	std::unordered_map<std::string, ComPtr<ID3D11ShaderResourceView>> texture_map;
	HRESULT load_texture(const std::string&, const WCHAR*);
	void set_texture(const std::string&);
};