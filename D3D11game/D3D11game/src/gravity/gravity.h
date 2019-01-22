/**
* @file gravity.h
* @brief 重力系のクラスを宣言
* @author 石山　悠
* @date 2018/10/29
*/
#pragma once
#include "../common/common.h"
#include <saki/transform/transform.h>
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
	static constexpr float gravity = -40.0f;
	//最大重力（移動量）
	static constexpr float max_gravity = 30.0f;
	//最大横移動速度
	float max_speed = 0;
	//上に働く力
	Vec2 power = Vec2(0, 0);
	//経過時間
	int time = 1;
	//頭がぶつかったかどうか
	bool hit_head = false;
public:
	/**
	* @brief 初期化
	* @param _max_speed 最大スピード
	*/
	void Init(const float _max_speed)
	{
		max_speed = _max_speed;
	}
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
	Vec3 AddGravity();
	/**
	* @brief 重力加速度のセット(ジャンプ)
	* @param up_power 加速度
	* @return bool ジャンプできたかどうか
	*/
	bool SetUpPower(const float up_power)
	{
		if (time == 0)
		{
			power.y = up_power;
			return true;
		}
		return false;
	}
	/**
	* @brief 横移動の加速度のセット
	* @param side_power 加速度
	*/
	void SetSidePower(const float side_power)
	{
		power.x += side_power;
		if (std::abs(power.x) > max_speed)
		{
			power.x = power.x > 0 ? max_speed : -max_speed;
		}
	}
	/**
	* @param 重力系のリセット
	*/
	void ResetGravity()
	{
		time = 0;
		power.y = 0;
		hit_head = false;
	}
	/**
	* @param 重力系の横方向のみリセット
	*/
	void ResetSideGravity()
	{
		power.x = 0;
	}
	/**
	* @brief 天井に当たったらフラグを立てる
	*/
	void HitHead()
	{
		time = 0;
		hit_head = true;
	}
	bool ReturnZero(const float speed);
	/**
	* @brief 直接横の力を入れる
	* @param side_power 横の力
	*/
	void DirectSetSidePower(const float side_power)
	{
		power.x = side_power;
	}

	float GetSidePower()
	{
		return power.x;
	}

	void SetMaxSpeed(const float speed)
	{
		max_speed = speed;
	}
};