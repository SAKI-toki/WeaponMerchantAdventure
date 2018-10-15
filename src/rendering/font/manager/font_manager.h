/**
* @file font_manager.h
* @brief フォントを管理するクラスを宣言
* @author 石山　悠
* @date 2018/10/09
*/
#pragma once
#include "../../../common/singleton.h"
#include <SpriteFont.h>

/**
* @brief フォントを管理するクラス
*/
class FontManager :public Singleton<FontManager>
{
	//必要なもの
	std::unique_ptr<DirectX::SpriteFont> m_pSpriteFont;
public:
	void Init(ID3D11Device*, WCHAR*);
	~FontManager();


	/**
	* @brief SpriteFontのゲッタ
	* @return std::unique_ptr<DirectX::SpriteFont>&
	*/
	std::unique_ptr<DirectX::SpriteFont>& GetSpriteFont() { return m_pSpriteFont; }
};