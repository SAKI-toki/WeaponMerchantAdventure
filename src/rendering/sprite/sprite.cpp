/**
* @file sprite.cpp
* @brief Sprite�N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/10/19
*/
#include "sprite.h"
#include "../../../DeviceResources.h"
#include "../../../Main.h"
#include <WICTextureLoader.h>
#include <SpriteBatch.h>
#include "../../object/camera/camera.h"

/**
* @brief �e�p�����[�^��摜��ǂݍ���
* @param name map�ŊǗ����邽�߂̃L�[
* @param path �e�N�X�`���̃p�X
* @param h,w�@�e�N�X�`���̑傫��
* @param _all_render �e�N�X�`�������ׂĕ`�悷�邩�ǂ����i�A�j���[�V���������邩�ǂ����Ƃقړ��`�j
* @param r,g,b,a �F
*/
void Sprite::Init(std::string name, WCHAR* path, const bool _all_render, const LONG w, const LONG h, const float r, const float g, const float b, const float a)
{
	//�e�N�X�`���̃T�C�Y����
	rect = { 0,0,w,h };
	my_name = name;
	//���ׂĕ`�悷�邩�ǂ���
	all_render = _all_render;
	color.r = r; color.g = g; color.b = b; color.a = a;
	//�e�N�X�`�����Z�b�g
	SpriteManager::GetInstance()->SetTexture(name, path);
}

/**
* @brief SpriteBatch���o�R���ĕ`�悷��
* @param transform �ʒu���]�A�g��E�k��
* @param affected_camera �J�����̈ʒu�ɂ���ĕ`�悷��ʒu��ς��邩�ǂ���
*/
void Sprite::Render(const Transform& transform, bool affected_camera, bool center_axis)
{

	/*try {
		//�`��
		if (affected_camera)
		{
			SpriteManager::GetInstance()->GetSpriteBatch()->Draw(texture.Get(), transform.pos - Camera::GetInstance()->GetPos(), &rect, _color, transform.rot, { (center_axis)?rect.right / 2.0f:0.0f,(center_axis) ? rect.bottom / 2.0f : 0.0f }, transform.scale);
		}
		else
		{
			SpriteManager::GetInstance()->GetSpriteBatch()->Draw(texture.Get(), transform.pos, &rect, _color, transform.rot, { (center_axis) ? rect.right / 2.0f : 0.0f,(center_axis) ? rect.bottom / 2.0f : 0.0f }, transform.scale);
		}
	}
	catch (std::exception& e)
	{
		WCHAR str[100];
		auto s = e.what();
		size_t len = 0;
		mbstowcs_s(&len, str, 50, s, _TRUNCATE);
		Comment(str, L"");
	}*/
	//�����o�ϐ��ɂ���ƃA���C�����g���ǂ��̂����̂ƌ�����̂ł����ŕϊ�
	DirectX::XMVECTOR _color = DirectX::XMVectorSet(color.r, color.g, color.b, color.a);
	SpriteManager::GetInstance()->Render(transform, affected_camera, center_axis, my_name, _color, rect);
}