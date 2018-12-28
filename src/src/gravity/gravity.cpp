/**
* @file gravity.cpp
* @brief 重力系のクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/29
*/
#include "gravity.h"

/**
* @brief 重力の追加
* @return VEC2 移動量
*/
Vec3 Gravity::AddGravity()
{
	++time;
	auto g = (((hit_head) ? 0 : power.y) + gravity * std::pow(time / 60.0f, 2.0f));
	return Vec3(power.x, g > std::abs(max_gravity) ? max_gravity : g,0);
}

/**
* @brief 横移動でスティック入力していないときの減速
* @param speed どのくらい減速するか
* @return bool スピードゼロになったかどうか
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