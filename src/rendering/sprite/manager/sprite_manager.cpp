/**
* @file sprite_manager.cpp
* @brief SpriteManagerクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/10/11
*/
#include "sprite_manager.h"
#include "../../font/manager/font_manager.h"
#include <WICTextureLoader.h>
#include "../../../common/common.h"

/**
* @brief 初期化
*/
void SpriteManager::Init()
{
	m_pSpriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);
	FontManager::GetInstance()->Init(device, L"resources/font/sample.spritefont");
}

/**
* @brief テクスチャを保存し、返す
* @param name mapで管理するためのキー
* @param path テクスチャがあるパス
* @return CP<ID3D11ShaderResourceView>& テクスチャ
*/
CP<ID3D11ShaderResourceView>& SpriteManager::GetTexture(std::string name, WCHAR* path)
{
	auto itr = textureList.find(name);
	if (itr == end(textureList))
	{
		CP<ID3D11ShaderResourceView> texture;
		WCHAR _path[256];
		wcscpy_s(_path, texture_path);
		wcscat_s(_path, path);
		//テクスチャの読み込み
		if (FAILED(DirectX::CreateWICTextureFromFile(device, _path, nullptr, texture.ReleaseAndGetAddressOf())))
		{
			Comment(L"テクスチャが読み込めませんでした。", L"sprite.cpp");
		}
		//mapに挿入
		textureList.insert(std::make_pair(name, texture));
	}
	return textureList.at(name);
}

/**
* @brief デストラクタ
*/
SpriteManager::~SpriteManager()
{
	if (m_pSpriteBatch)m_pSpriteBatch.reset();
}