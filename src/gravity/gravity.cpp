/**
* @file gravity.cpp
* @brief �d�͌n�̃N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/15
*/
#include "gravity.h"

/**
* @brief �d�͂̒ǉ�
*/
float Gravity::AddGravity()
{
	++time;
	auto g = (((hit_head) ? 0 : power) + gravity * std::pow(time / 60.0f, 2.0f))*-1;
	return g < max_gravity ? max_gravity : g;
}