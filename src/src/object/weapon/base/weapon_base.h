/**
* @file weapon_base.h
* @brief ����̃X�[�p�[�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/15
*/
#pragma once
#include "../../../common/common.h"

/**
* @brief ����̃X�[�p�[�N���X
*/
class WeaponBase
{
public:
	bool weapon_enabled = true;
	virtual bool Attack(bool,const Vec3&) = 0;
	virtual void WeaponStart() = 0;
	virtual void WeaponUpdate(const Vec3&, bool) = 0;
	virtual void WeaponRender(const Transform& =
		Transform{ saki::vector3_zero<float>,saki::vector3_zero<float>,saki::vector3_zero<float> }) = 0;
	virtual void WeaponDestroy() = 0;
	virtual ~WeaponBase() {}
};
