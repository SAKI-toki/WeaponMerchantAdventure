/**
* @file font_manager.cpp
* @brief �t�H���g���Ǘ�����N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/09
*/
#include "font_manager.h"

/**
* @brief ������
* @param device ID3D11Device
* @param path �t�H���g�̃p�X
*/
void FontManager::Init(ID3D11Device* device,WCHAR* path)
{
	m_pSpriteFont = std::make_unique<DirectX::SpriteFont>(device, path);
}

/**
* @brief �f�X�g���N�^
*/
FontManager::~FontManager()
{
	if (m_pSpriteFont)m_pSpriteFont.reset();
}