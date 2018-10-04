/**
* @file sprite.cpp
* @brief Sprite�N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/10/04
*/
#include "sprite.h"
#include "../../../DeviceResources.h"
#include "../../../Main.h"
#include <WICTextureLoader.h>

/**
* @brief �e�p�����[�^��摜��ǂݍ���
* @param path �e�N�X�`���̃p�X
* @param h,w�@�e�N�X�`���̑傫��
* @param r,g,b,a �F
*/
void Sprite::Init(WCHAR* path, const int h, const int w, float r, float g, float b, float a)
{
	height = h; width = w;
	color.r = r; color.g = g; color.b = b; color.a = a;
	//�e�N�X�`�����擾
	texture = SpriteManager::GetInstance()->GetTexture(path);
}

/**
* @brief SpriteBatch���o�R���ĕ`�悷��
* @param t �ʒu���]�A�g��E�k���̃N���X
*/
void Sprite::Render(const Transform& t)
{
	//�����o�ϐ��ɂ���ƃA���C�����g���ǂ��̂����̂ƌ�����̂ł����ŕϊ�
	DirectX::XMVECTOR _color = DirectX::XMVectorSet(color.r, color.g, color.b, color.a);
	//�`��
	SpriteManager::GetInstance()->GetSpriteBatch()->Draw(texture.Get(), t.pos, nullptr, _color, 0.0f, t.pos);
}