#pragma once
#include "../common/common.h"
#include <string>
#include "manager/texture_manager.h"
class Texture
{
	std::string name;
public:
	HRESULT load_texture(const std::string& key, const WCHAR* path)
	{
		name = key;
		return TextureManager::getinstance()->load_texture(key, path);
	}
	void set_texture()
	{
		TextureManager::getinstance()->set_texture(name);
	}
};