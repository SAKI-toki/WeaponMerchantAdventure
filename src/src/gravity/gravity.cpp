/**
* @file gravity.cpp
* @brief �d�͌n�̃N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/29
*/
#include "gravity.h"

/**
* @brief �d�͂̒ǉ�
* @return VEC2 �ړ���
*/
Vec3 Gravity::AddGravity()
{
	++time;
	auto g = (((hit_head) ? 0 : power.y) + gravity * std::pow(time / 60.0f, 2.0f));
	return Vec3(power.x, g > std::abs(max_gravity) ? max_gravity : g,0);
}

/**
* @brief ���ړ��ŃX�e�B�b�N���͂��Ă��Ȃ��Ƃ��̌���
* @param speed �ǂ̂��炢�������邩
* @return bool �X�s�[�h�[���ɂȂ������ǂ���
*/
bool Gravity::ReturnZero(const float speed)
{
	if (power.x == 0)return true;
	auto prev = power.x;
	power.x -= power.x > 0 ? speed : -speed;
	if (prev > 0 && power.x < 0 ||
		prev < 0 && power.x > 0)
	{
		power.x = 0;
	}
	if (power.x == 0)return true;
	else return false;
}