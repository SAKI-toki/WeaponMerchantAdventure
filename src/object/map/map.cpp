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
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}
/**
* @brief �}�b�v�̍X�V
*/
void MapObject::UpdateProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}
/**
* @brief �}�b�v�̔j��
*/
void MapObject::Destroy()
{
	if (collider.enabled)collider.Destroy();
}

/**
* @brief �}�b�v���������Ă�Ƃ��Ɏ��s����֐�
*/
void MapObject::Collision(ObjectBase* obj, VEC2)
{
}
