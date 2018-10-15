/**
* @file font_manager.h
* @brief �t�H���g���Ǘ�����N���X��錾
* @author �ΎR�@�I
* @date 2018/10/09
*/
#pragma once
#include "../../../common/singleton.h"
#include <SpriteFont.h>

/**
* @brief �t�H���g���Ǘ�����N���X
*/
class FontManager :public Singleton<FontManager>
{
	//�K�v�Ȃ���
	std::unique_ptr<DirectX::SpriteFont> m_pSpriteFont;
public:
	void Init(ID3D11Device*, WCHAR*);
	~FontManager();


	/**
	* @brief SpriteFont�̃Q�b�^
	* @return std::unique_ptr<DirectX::SpriteFont>&
	*/
	std::unique_ptr<DirectX::SpriteFont>& GetSpriteFont() { return m_pSpriteFont; }
};