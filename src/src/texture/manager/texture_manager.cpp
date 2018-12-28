#include "texture_manager.h"
#include "../../device/device.h"
#include <WICTexture/WICTextureLoader.h>
extern void ExitGame();

HRESULT TextureManager::load_texture(const std::string& key, const WCHAR* path)
{
	auto itr = texture_map.find(key);
	if (itr == end(texture_map))
	{
		WCHAR _path[256];
		wcscpy_s(_path, texture_path);
		wcscat_s(_path, path);
		ID3D11Resource* temp = nullptr;
		ComPtr<ID3D11ShaderResourceView> texture;
		if (FAILED(DirectX::CreateWICTextureFromFile(
			Device::getinstance()->device.Get(), _path, &temp, texture.GetAddressOf())))
		{
			Comment(L"ƒeƒNƒXƒ`ƒƒ‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s", L"texture_manager.cpp");
			return E_FAIL;
		}
		texture_map.insert(std::make_pair(key, texture));
	}

	return S_OK;
}
void TextureManager::set_texture(const std::string& key)
{
	auto itr = texture_map.find(key);
	if (itr == end(texture_map))
	{
		Comment(L"“o˜^‚µ‚Ä‚¢‚È‚¢texture‚ðŽg—p‚µ‚æ‚¤‚Æ‚µ‚Ä‚¢‚Ü‚·", L"texture_manager.cpp");
		ExitGame();
	}
	else
	{
		Device::getinstance()->immediate_context->
			PSSetShaderResources(0, 1, itr->second.GetAddressOf());
	}
}