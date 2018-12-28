/**
* @file map.cpp
* @brief �}�b�v�ɔz�u����I�u�W�F�N�g�̃N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/11
*/
#include "map.h"

/**
* @brief ������
*/
void MapObject::InitProcess()
{
	collider.SetStatus(transform.get_pos(), size.x,
		size.y, transform.get_scale());
	if (is_mapchip)
	{
		sprite.slice_num = Vec2{ 16,8 };
		sprite.current_slice = Vec2{ 16 ,2 };
		//sprite.SetRect(RECT{ 448 + 32,32,480 + 32,32 + 32 });
	}
}

/**
* @brief �}�b�v�̍X�V
*/
void MapObject::UpdateProcess()
{
	collider.SetStatus(transform.get_pos(), size.x,
		size.y, transform.get_scale());
}

/**
* @brief �}�b�v�̔j��
*/
void MapObject::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
}

/**
* @brief �}�b�v���������Ă�Ƃ��Ɏ��s����֐�
*/
void MapObject::Collision(ObjectBase* obj, Vec2)
{
	if (obj == nullptr)return;
}
