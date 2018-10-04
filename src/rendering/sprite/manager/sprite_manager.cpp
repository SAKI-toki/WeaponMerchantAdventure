/**
* @file sprite_manger.cpp
* @brief SpriteManagerクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/10/04
*/
#include "sprite_manager.h"
#include <WICTextureLoader.h>

/**
* @brief 初期化
*/
void SpriteManager::Init()
{
	m_pSpriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);
}

/**
* @brief テクスチャを保存し、返す
* @param path テクスチャがあるパス
* @return CP<ID3D11ShaderResourceView>& テクスチャ
*/
CP<ID3D11ShaderResourceView>& SpriteManager::GetTexture(WCHAR* path)
{
	auto itr = textureList.find(path);
	if (itr == end(textureList))
	{
		CP<ID3D11ShaderResourceView> texture;
		//テクスチャの読み込み
		if (FAILED(DirectX::CreateWICTextureFromFile(device, path, nullptr, texture.ReleaseAndGetAddressOf())))
		{
			MessageBox(NULL, L"テクスチャが読み込めませんでした。", L"sprite.cpp", MB_OK);
		}
		//mapに挿入
		textureList.insert(std::make_pair(path, texture));
	}
	return textureList.at(path);
}

/**
* @brief デストラクタ
*/
SpriteManager::~SpriteManager()
{
	m_pSpriteBatch.reset();
}