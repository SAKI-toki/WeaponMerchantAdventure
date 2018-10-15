/**
* @file square_collider.cpp
* @brief �l�p�`�̃R���C�_�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/12
*/
#include "square_collider.h"
#include "../manager/collider_manager.h"

/**
* @brief �R���X�g���N�^
* @param obj �I�u�W�F�N�g
*/
SquareCollider::SquareCollider(ObjectBase* obj, bool _is_trigger, bool is_static)
	:ColliderBase(obj, _is_trigger)
{
	ColliderManager::GetInstance()->SetCollider(this, is_static);
}

/**
* @brief �����蔻��̃X�e�[�^�X���Z�b�g����
* @param pos �Z���^�[�̈ʒu
* @param w,h ���A����
* @param rot ��]
*/
void SquareCollider::SetStatus(VEC2 pos, float w, float h, float rot)
{
	status.center_pos = pos, status.width = w / 2.0f, status.height = h / 2.0f, status.rot = rot;
}
/**
* @brief ���������Ƃ��̉����o��
* @param pos �ړ���
* @detail ���Z���Z�ɂ��Ȃ����R��float�̌덷���N���ăo�O��Ȃ��悤�ɂ��邽��
*/
void SquareCollider::CollisionExtrusion(const VEC2& pos)
{
	status.center_pos = pos;
	object->transform.pos = pos;
}
/**
* @brief �l�p�`�̃R���C�_�̔j��
*/
void SquareCollider::Destroy()
{
	ColliderManager::GetInstance()->DeleteCollider(this);
	enabled = false;
}