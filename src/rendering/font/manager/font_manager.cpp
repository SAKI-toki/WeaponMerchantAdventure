/**
* @file font_manager.cpp
* @brief フォントを管理するクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/09
*/
#include "font_manager.h"

/**
* @brief 初期化
* @param device ID3D11Device
* @param path フォントのパス
*/
void FontManager::Init(ID3D11Device* device,WCHAR* path)
{
	m_pSpriteFont = std::make_unique<DirectX::SpriteFont>(device, path);
}

/**
* @brief デストラクタ
*/
FontManager::~FontManager()
{
	if (m_pSpriteFont)m_pSpriteFont.reset();
}