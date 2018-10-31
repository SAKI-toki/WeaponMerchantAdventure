/**
* @file animation.h
* @brief アニメーションクラスの宣言
* @author 石山　悠
* @date 2018/10/29
*/
#pragma once
#include "../transform/transform.h"

/**
* @brief アニメーションクラス
*/
class Animation
{
	//一つのサイズ
	VEC2 one_size;
	//縦の数
	int ver_num;
	//横の数
	int hor_num;
	//間隔
	int interval;
	//現在のアニメーションの位置
	int current_ver_num = INT_MAX;
	int current_hor_num;
	//次のアニメーションをする時間
	int time;
	int current_time = 0;
public:
	void Init(const VEC2&, const int, const int, const int);
	void Update();
	RECT GetAnimation()const;
	void ChangeAnimation(const int, const int, const bool = false);
};