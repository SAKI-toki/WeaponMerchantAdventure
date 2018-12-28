/**
* @file collider_base.h
* @brief �R���C�_�̃X�[�p�[�N���X�̐錾�A��`
* @author �ΎR�@�I
* @date 2018/10/11
*/
#pragma once
#include "../../common/common.h"
#include "../../object/base/object_base.h"
#include <functional>
/**
* @brief �R���C�_�̃X�[�p�[�N���X
*/
class ColliderBase
{
public:
	//���������Ƃ��ɏ�����t���O
	bool collision_destroy = false;
	//�����o�����邩�ǂ���
	bool is_trigger;
	//x�����ɑ΂��ĉ����o�����Ȃ����̂Ԃ��������ǂ���
	bool collision_is_static_x = false;
	//y�����ɑ΂��ĉ����o�����Ȃ����̂Ԃ��������ǂ���
	bool collision_is_static_y = false;
	//���̃R���C�_�����I�u�W�F�N�g
	ObjectBase* object;
	//�������Ă���Ƃ��Ɏ��s����֐�
	std::function<void(ObjectBase*,Vec2)> collision_func;
	//���肷�邩�ǂ���
	bool enabled = true;

	/**
	* @brief �R���X�g���N�^
	* @param obj �I�u�W�F�N�g
	* @param _is_trigger �����o�����邩�ǂ���
	*/
	ColliderBase(ObjectBase* obj, bool _is_trigger = false) :
		object(obj), is_trigger(_is_trigger)
	{
		//���������Ƃ��Ɏ��s����֐����i�[
		collision_func = std::bind(&ObjectBase::Collision, obj, std::placeholders::_1, std::placeholders::_2);
	}

	/**
	* @brief �R�s�[������Z�q
	*/
	ColliderBase& operator=(const ColliderBase& other)
	{
		if (this != &other)
		{
			this->collision_func = other.collision_func;
			this->collision_is_static_x = other.collision_is_static_x;
			this->collision_is_static_y = other.collision_is_static_y;
			this->enabled = other.enabled;
			this->is_trigger = other.is_trigger;
			this->object = other.object;
		}
		return *this;
	}

	virtual ~ColliderBase() {}
};