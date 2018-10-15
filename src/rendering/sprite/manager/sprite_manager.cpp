/**
* @file sprite_manager.cpp
* @brief SpriteManager�N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/10/11
*/
#include "sprite_manager.h"
#include "../../font/manager/font_manager.h"
#include <WICTextureLoader.h>
#include "../../../common/common.h"

/**
* @brief ������
*/
void SpriteManager::Init()
{
	m_pSpriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);
	FontManager::GetInstance()->Init(device, L"resources/font/sample.spritefont");
}

/**
* @brief �e�N�X�`����ۑ����A�Ԃ�
* @param name map�ŊǗ����邽�߂̃L�[
* @param path �e�N�X�`��������p�X
* @return CP<ID3D11ShaderResourceView>& �e�N�X�`��
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
		//�e�N�X�`���̓ǂݍ���
		if (FAILED(DirectX::CreateWICTextureFromFile(device, _path, nullptr, texture.ReleaseAndGetAddressOf())))
		{
			Comment(L"�e�N�X�`�����ǂݍ��߂܂���ł����B", L"sprite.cpp");
		}
		//map�ɑ}��
		textureList.insert(std::make_pair(name, texture));
	}
	return textureList.at(name);
}

/**
* @brief �f�X�g���N�^
*/
SpriteManager::~SpriteManager()
{
	if (m_pSpriteBatch)m_pSpriteBatch.reset();
}