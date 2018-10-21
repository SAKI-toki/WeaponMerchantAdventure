/**
* @file gravity.h
* @brief 重力系のクラスを宣言
* @author 石山　悠
* @date 2018/10/15
*/
#pragma once
#include "../common/common.h"
#include <cmath>
/**
* @brief 重力を管理するクラス
*/
class Gravity
{
	//重力加速度
	/*
	移動量(y)=上に働く力+重力加速度*時間(s)*時間(s)
	*/
	static constexpr float gravity = -30.0f;
	//最大重力（移動量）
	static constexpr float max_gravity = -20.0f;
	//上に働く力
	float power = 0;
	//経過時間
	int time = 0;
	//頭がぶつかったかどうか
	bool hit_head = false;
public:
	/**
	* @brief コピー代入演算子
	*/
	Gravity& operator=(const Gravity& other)
	{
		if (this != &other)
		{
			this->power = other.power;
			this->time = other.time;
			this->hit_head = other.hit_head;
		}
		return *this;
	}
	float AddGravity();
	/**
	* @brief 加速度のセット
	* @param 加速度
	*/
	void SetPower(const float _power)
	{
		if (time == 0)power = _power;
	}
	/**
	* @param 重力系のリセット
	*/
	void ResetGravity()
	{
		time = 0;
		power = 0;
		hit_head = false;
	}
	/**
	* @brief 天井に当たったらフラグを立てる
	*/
	void HitHead()
	{
		time = 0;
		hit_head = true;
	}
};