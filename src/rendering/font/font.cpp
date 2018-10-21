/**
* @file font.cpp
* @brief �t�H���g�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/09
*/
#include "font.h"
#include "../sprite/manager/sprite_manager.h"

/**
* @brief ������
* @param _text �e�L�X�g
* @param r,g,b,a �F
*/
void Font::Init(WCHAR* _text, float r, float g, float b, float a)
{
	SetText(_text);
	color.r = r; color.g = g; color.b = b; color.a = a;
}

/**
* @brief �`��
*/
void Font::Render()
{

	//�����o�ϐ��ɂ���ƃA���C�����g���ǂ��̂����̂ƌ�����̂ł����ŕϊ�
	DirectX::XMVECTOR _color = DirectX::XMVectorSet(color.r, color.g, color.b, color.a);
	//�`��
	FontManager::GetInstance()->GetSpriteFont()->DrawString(SpriteManager::GetInstance()->GetSpriteBatch().get(),
		text, transform.pos, _color, transform.rot, { 0,0 }, transform.scale);
}