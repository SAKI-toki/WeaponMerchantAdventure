/**
* @file transform.h
* @brief transformクラスを宣言
* @author 石山　悠
* @date 2018/10/06
*/
#pragma once
#include <SimpleMath.h>
using VEC2 = DirectX::SimpleMath::Vector2;

/**
* @transformクラス
*/
class Transform
{
public:
	VEC2 pos;	//位置
	float rot;	//回転
	float scale;//拡大・縮小

	//コンストラクタ
	Transform();
	Transform(const float, const float = 0, const float = 0, const float = 1);
	Transform(const VEC2& _pos, const float _rot, const float _scale);
	//コピーコンストラクタ
	Transform(const Transform& t);
	//初期化
	void Init(const float, const float = 0, const float = 0, const float = 1);
	void Init(const VEC2& _pos, const float _rot, const float _scale);
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