/**
* @file dynamic_object.h
* @brief �����I�u�W�F�N�g�̃X�[�p�[�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/04
*/
#pragma once
#include "../object_base.h"

/**
* @brief �����I�u�W�F�N�g�̃X�[�p�[�N���X
*/
class DynamicObject :public ObjectBase
{
protected:
	virtual void RenderProcess(bool);
public:
	/**
	* @brief �R���X�g���N�^
	*/
	DynamicObject() :ObjectBase(true) {}
	/**
	* @brief �R�s�[������Z�q
	*/
	DynamicObject& operator=(const DynamicObject& other)
	{
		if (this != &other)
		{
			ObjectBase::operator=(other);
		}
		return *this;
	}
	virtual ~DynamicObject() {}
};