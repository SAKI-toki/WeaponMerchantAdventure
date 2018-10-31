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
* @param _is_trigger ���������Ƃ��ɓ����邩�ǂ���
* @param _is_static �ÓI���ǂ���
*/
SquareCollider::SquareCollider(ObjectBase* obj, bool _is_trigger, bool _is_static)
	:ColliderBase(obj, _is_trigger), is_static(_is_static)
{
	ColliderManager::GetInstance()->SetCollider(this, _is_static);
}

/**
* @brief �����蔻��̃X�e�[�^�X���Z�b�g����
* @param pos �Z���^�[�̈ʒu
* @param w,h ���A����
* @param rot ��]
* @param scale �g��E�k��
*/
void SquareCollider::SetStatus(const VEC2& pos, const float w, const float h, const float rot, const float scale)
{
	status.center_pos = pos, status.width = w * 0.5f*scale, status.height = h * 0.5f*scale, status.rot = rot;

}
/**
* @brief ���������Ƃ��̉����o��
* @param pos �ړ���
* @details ���Z���Z�ɂ��Ȃ����R��float�̌덷���N���ăo�O��Ȃ��悤�ɂ��邽��
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

/**
* @brief �R�s�[������Z�q
*/
SquareCollider& SquareCollider::operator=(const SquareCollider& other)
{
	if (this != &other)
	{
		this->status = other.status;
		ColliderBase::operator=(other);
		ColliderManager::GetInstance()->SetCollider(this, is_static);
	}
	return *this;
}
