/**
* @file gravity.cpp
* @brief 重力系のクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/15
*/
#include "gravity.h"

/**
* @brief 重力の追加
*/
float Gravity::AddGravity()
{
	++time;
	auto g = (((hit_head) ? 0 : power) + gravity * std::pow(time / 60.0f, 2.0f))*-1;
	return g < max_gravity ? max_gravity : g;
}