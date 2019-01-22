/**
* @file animation.h
* @brief アニメーションクラスの宣言
* @author 石山　悠
* @date 2018/10/29
*/
#pragma once
#include "../common/common.h"

/**
* @brief アニメーションクラス
*/
class Animation
{
	//一つのサイズ
	Vec2 one_size;
	//縦の数
	int ver_num;
	//横の数
	int hor_num;
	//間隔
	int interval;
	//現在のアニメーションの位置
	int current_ver_num = INT_MAX;
	int current_hor_num = 0;
	//次のアニメーションをする時間
	int time;
	int current_time = 0;
public:
	Animation() {}
	void Changetime(const int t) { time = t; }
	/**
	* @brief コピーコンストラクタ
	*/
	Animation(const Animation& other)
	{
		this->one_size = other.one_size;
		this->ver_num = other.ver_num;
		this->hor_num = other.hor_num;
		this->interval = other.interval;
		this->current_ver_num = other.current_ver_num;
		this->current_hor_num = other.current_hor_num;
		this->time = other.time;
		this->current_time = other.current_time;
	}
	/**
	* @brief コピー代入演算子
	*/
	Animation& operator=(const Animation& other)
	{
		if (this != &other)
		{
			this->one_size = other.one_size;
			this->ver_num = other.ver_num;
			this->hor_num = other.hor_num;
			this->interval = other.interval;
			this->current_ver_num = other.current_ver_num;
			this->current_hor_num = other.current_hor_num;
			this->time = other.time;
			this->current_time = other.current_time;
		}
		return *this;
	}
	void Init(const Vec2&, const int, const int, const int);
	void Update();
	Vec2 GetAnimation()const;
	void ChangeAnimation(const int, const int, const bool = false);
};