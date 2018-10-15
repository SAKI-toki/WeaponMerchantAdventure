/**
* @file collider_base.h
* @brief �R���C�_�̃X�[�p�[�N���X�̐錾�A��`
* @author �ΎR�@�I
* @date 2018/10/11
*/
#pragma once
#include "../../object/base/object_base.h"

/**
* @brief �R���C�_�̃X�[�p�[�N���X
*/
class ColliderBase
{
public:
	//�����o�����邩�ǂ���
	const bool is_trigger;
	//x�����ɑ΂��ĉ����o�����Ȃ����̂Ԃ��������ǂ���
	bool collision_is_trigger_x;
	//y�����ɑ΂��ĉ����o�����Ȃ����̂Ԃ��������ǂ���
	bool collision_is_trigger_y;
	//���̃R���C�_�����I�u�W�F�N�g
	ObjectBase* object;
	//�������Ă���Ƃ��Ɏ��s����֐�
	std::function<void(ObjectBase*,VEC2)> collision_func;
	//���肷�邩�ǂ���
	bool enabled;

	/**
	* @brief �R���X�g���N�^
	* @param obj �I�u�W�F�N�g
	* @param _is_trigger �����o�����邩�ǂ���
	*/
	ColliderBase(ObjectBase* obj, bool _is_trigger = false) :
		enabled(true), object(obj), is_trigger(_is_trigger), collision_is_trigger_x(false), collision_is_trigger_y(false)
	{
		//���������Ƃ��Ɏ��s����֐����i�[
		collision_func = std::bind(&ObjectBase::Collision, obj, std::placeholders::_1, std::placeholders::_2);
	}

	virtual ~ColliderBase() {}
};