/**
* @file transform.h
* @brief transformクラスを宣言
* @author 石山　悠
* @date 2018/10/04
*/
#pragma once
#include <SimpleMath.h>
using VEC2 = DirectX::SimpleMath::Vector2;
using VEC3 = DirectX::SimpleMath::Vector3;

/**
* @transformクラス
*/
class Transform
{
public:
	VEC2 pos;	//位置
	VEC3 rot;	//回転
	VEC2 scale;	//拡大・縮小

	//コンストラクタ
	Transform();
	Transform(const float, const float = 0, const float = 0, const float = 0, const float = 0, const float = 0, const float = 0);
	Transform(const VEC2& _pos, const VEC3& _rot, const VEC2& _scale);
	Transform(const Transform& t);

	//移動
	void Move(const float, const float);
	void Move(const VEC2&);

	//回転
	void Rotate(const float, const float, const float);
	void Rotate(const VEC3&);

	//拡大・縮小
	void Scaling(const float, const float);
	void Scaling(const VEC2&);

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