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
	void RenderProcess(bool);
public:
	virtual ~DynamicObject() {}
};