/**
* @file weapon_base.h
* @brief ����̃X�[�p�[�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/15
*/
#pragma once
#include "../../../transform/transform.h"

/**
* @brief ����̃X�[�p�[�N���X
*/
class WeaponBase
{
public:
	bool weapon_enabled = true;
	virtual void Attack(bool,const VEC2&) = 0;
	virtual void WeaponStart() = 0;
	virtual void WeaponUpdate(const VEC2&, bool) = 0;
	virtual void WeaponRender(const Transform& = NULL) = 0;
	virtual void WeaponDestroy() = 0;
	virtual ~WeaponBase() {}
};
