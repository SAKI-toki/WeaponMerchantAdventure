/**
* @file sprite_manger.cpp
* @brief SpriteManager�N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/10/04
*/
#include "sprite_manager.h"
#include <WICTextureLoader.h>

/**
* @brief ������
*/
void SpriteManager::Init()
{
	m_pSpriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);
}

/**
* @brief �e�N�X�`����ۑ����A�Ԃ�
* @param path �e�N�X�`��������p�X
* @return CP<ID3D11ShaderResourceView>& �e�N�X�`��
*/
CP<ID3D11ShaderResourceView>& SpriteManager::GetTexture(WCHAR* path)
{
	auto itr = textureList.find(path);
	if (itr == end(textureList))
	{
		CP<ID3D11ShaderResourceView> texture;
		//�e�N�X�`���̓ǂݍ���
		if (FAILED(DirectX::CreateWICTextureFromFile(device, path, nullptr, texture.ReleaseAndGetAddressOf())))
		{
			MessageBox(NULL, L"�e�N�X�`�����ǂݍ��߂܂���ł����B", L"sprite.cpp", MB_OK);
		}
		//map�ɑ}��
		textureList.insert(std::make_pair(path, texture));
	}
	return textureList.at(path);
}

/**
* @brief �f�X�g���N�^
*/
SpriteManager::~SpriteManager()
{
	m_pSpriteBatch.reset();
}