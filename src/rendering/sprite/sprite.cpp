/**
* @file sprite.cpp
* @brief Sprite�N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/10/06
*/
#include "sprite.h"
#include "../../../DeviceResources.h"
#include "../../../Main.h"
#include <WICTextureLoader.h>
#include <SpriteBatch.h>

/**
* @brief Transform�N���X���󂯎��R���X�g���N�^
* @param t Transform�N���X
*/
Sprite::Sprite(const Transform& t) :
	transform(t) {}
/**
* @brief �e�p�����[�^��摜��ǂݍ���
* @param path �e�N�X�`���̃p�X
* @param h,w�@�e�N�X�`���̑傫��
* @param _all_render �e�N�X�`�������ׂĕ`�悷�邩�ǂ����i�A�j���[�V���������邩�ǂ����Ƃقړ��`�j
* @param r,g,b,a �F
*/
void Sprite::Init(WCHAR* path, const bool _all_render, const LONG w, const LONG h, const float r, const float g, const float b, const float a)
{
	rect = { 0,0,w,h };
	all_render = _all_render;
	color.r = r; color.g = g; color.b = b; color.a = a;
	//�e�N�X�`�����擾
	texture = SpriteManager::GetInstance()->GetTexture(path);
}

/**
* @brief SpriteBatch���o�R���ĕ`�悷��
*/
void Sprite::Render()
{
	//�����o�ϐ��ɂ���ƃA���C�����g���ǂ��̂����̂ƌ�����̂ł����ŕϊ�
	DirectX::XMVECTOR _color = DirectX::XMVectorSet(color.r, color.g, color.b, color.a);
	//�`��
	SpriteManager::GetInstance()->GetSpriteBatch()->Draw(texture.Get(), transform.pos, &rect, _color, transform.rot, { rect.right / 2.0f,rect.bottom / 2.0f }, transform.scale);
}