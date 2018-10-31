/**
* @file transform.h
* @brief transformクラスを宣言
* @author 石山　悠
* @date 2018/10/09
*/
#pragma once
#include "../common/common.h"
#include <SpriteBatch.h>

/**
* @brief transformクラス
*/
class Transform
{
public:
	VEC2 pos = VEC2::Zero;	//位置
	float rot = 0.0f;	//回転
	float scale = 0.0f;//拡大・縮小
	VEC2 size = VEC2::Zero;//サイズ
	DirectX::SpriteEffects sprite_effect;//反転

	//コンストラクタ
	Transform() {}
	Transform(const float, const float = 0, const float = 0, const float = 1, const float = 0, const float = 0, const DirectX::SpriteEffects = DirectX::SpriteEffects_None);
	Transform(const VEC2& _pos, const float _rot, const float _scale, const VEC2& = VEC2::Zero, const DirectX::SpriteEffects = DirectX::SpriteEffects_None);

	//コピーコンストラクタ
	Transform(const Transform& t);

	//初期化
	void Init(const float, const float = 0, const float = 0, const float = 1, const float = 0, const float = 0, const DirectX::SpriteEffects = DirectX::SpriteEffects_None);
	void Init(const VEC2& _pos, const float _rot = 0, const float _scale = 0, const VEC2& = VEC2::Zero, const DirectX::SpriteEffects = DirectX::SpriteEffects_None);
	void Init(const Transform& t);

	//移動
	void Move(const float, const float);
	void Move(const VEC2&);

	//回転
	void Rotate(const float);

	//拡大・縮小
	void Scaling(const float);

	//代入や加減乗除用operator
	void operator=(const Transform&);
	void operator+=(const Transform&);
	void operator-=(const Transform&);
	void operator*=(const Transform&);
	void operator*=(const float);
	void operator/=(const float);
	Transform operator+(const Transform&)const;
	Transform operator-(const Transform&)const;
	//比較用operator
	bool operator==(const Transform&)const;
	bool operator!=(const Transform&)const;
};