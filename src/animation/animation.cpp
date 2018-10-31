/**
* @file animation.cpp
* @brief アニメーションクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/29
*/
#include "animation.h"

/**
* @brief 初期化
* @param _one 一つ当たりの大きさ
* @param hor 横の数
* @param ver 縦の数
* @param _inter 一つ一つの間隔
*/
void Animation::Init(const VEC2& _one, const int hor, const int ver, const int _inter)
{
	one_size = _one;
	hor_num = hor;
	ver_num = ver;
	interval = _inter;
}

/**
* @brief 更新
*/
void Animation::Update()
{
	//時間が来たら次のアニメーション
	if (++current_time > time)
	{
		current_time = 0;
		//一番右端まで来たら最初に戻る
		if (++current_hor_num >= hor_num)
		{
			current_hor_num = 0;
		}
	}
}

/**
* @brief アニメーションを変更する
* @return RECT テクスチャで描画する部分
*/
RECT Animation::GetAnimation()const
{
	return { (static_cast<LONG>(one_size.x) + interval)*current_hor_num,(static_cast<LONG>(one_size.y) + interval)*current_ver_num,
		(static_cast<LONG>(one_size.x) + interval)*current_hor_num + static_cast<LONG>(one_size.x) - 1, (static_cast<LONG>(one_size.y) + interval)*current_ver_num + static_cast<LONG>(one_size.y) - 1 };
}

/**
* @brief アニメーションを変える
* @param vertical 上から何番目のアニメーションにするか(0スタート)
* @param _time 何フレームごとに変更するか
* @param reset アニメーションを最初からするかどうか
*/
void Animation::ChangeAnimation(const int vertical, const int _time, const bool reset)
{
	if (current_ver_num == vertical)return;
	current_ver_num = vertical;
	time = _time;
	current_time = 0;
	if (reset)
	{
		current_hor_num = 0;
	}
}