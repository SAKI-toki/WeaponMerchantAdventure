/**
* @file camera.h
* @brief �J�����N���X��錾
* @author �ΎR�@�I
* @date 2018/10/09
*/
#pragma once
#include "../../common/singleton.h"
#include "../../transform/transform.h"
#include "../base/object_base.h"


/**
* @brief �J�����N���X
*/
class Camera :public Singleton<Camera>
{
	//�J�����̈ʒu
	VEC2 camera_pos = VEC2::Zero;
	//�ǔ�������^�[�Q�b�g
	ObjectBase* target = nullptr;
public:
	Camera() {}
	Camera(const VEC2&);
	void Move(const VEC2&);
	void SetPos(const VEC2&);
	VEC2 GetPos()const;
	void Update();
	/**
	* brief �^�[�Q�b�g�̃Z�b�g
	*/
	void SetTarget(ObjectBase* t)
	{
		target = t;
	}
};