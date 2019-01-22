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
	virtual void CollisionProcess(ObjectBase*, Vec2) {}
public:
	/**
	* @brief �R���X�g���N�^
	*/
	StaticObject() :ObjectBase(false) {}
	StaticObject(const StaticObject& other) :ObjectBase(other)
	{
	}
	/**
	* @brief �R�s�[������Z�q
	*/
	StaticObject& operator=(const StaticObject& other)
	{
		if (this != &other)
		{
			ObjectBase::operator=(other);
		}
		return *this;
	}
	virtual void Destroy(){}
	virtual void Collision(ObjectBase*, Vec2) {}
	
	virtual ~StaticObject() {}

	void SetColor(const float, const float, const float, const float);
};