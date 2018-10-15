/**
* @file static_object.h
* @brief �����Ȃ��I�u�W�F�N�g�̃X�[�p�[�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/04
*/
#pragma once
#include "../object_base.h"
/**
* @brief �����Ȃ��I�u�W�F�N�g�̃X�[�p�[�N���X
*/
class StaticObject :public ObjectBase
{
protected:
	void RenderProcess(bool);
	virtual void InitProcess() {}
	virtual void UpdateProcess() {}
	virtual void CollisionProcess(ObjectBase*,VEC2) {}
public:
	virtual void Destroy(){}
	virtual void Collision(ObjectBase*, VEC2) {}
	
	virtual ~StaticObject() {}
};