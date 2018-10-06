/**
* @file transform.cpp
* @brief transformクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/06
*/
#include "transform.h"

/**
* :brief　ゼロで初期化する引数なしコンストラクタ
*/
Transform::Transform() :
	pos(VEC2::Zero), rot(0.0f), scale(1.0f)
{}
/**
* @brief posをそれぞれのパラメータで受け取るコンストラクタ
*/
Transform::Transform(const float posx, const float posy, const float _rot, const float _scale):
	pos(VEC2(posx,posy)),rot(_rot),scale(_scale)
{}
/**
* @brief posをVEC2クラスで受け取るコンストラクタ
*/
Transform::Transform(const VEC2& _pos, const float _rot, const float _scale):
	pos(_pos),rot(_rot),scale(_scale)
{}
/**
* @brief コピーコンストラクタ
*/
Transform::Transform(const Transform& t)
{
	this->Init(t);
}
/**
* @brief 一つ一つ値で渡す初期化
*/
void Transform::Init(const float posx, const  float posy, const float _rot, const  float _scale)
{
	pos = { posx,posy };
	rot = _rot;
	scale = _scale;
}
/**
* @brief 各クラスに対して値を渡す初期化
*/
void Transform::Init(const VEC2& _pos, const float _rot, const float _scale)
{
	pos = _pos;
	rot = _rot;
	scale = _scale;
}
/**
* @brief Transformクラスを渡す初期化
*/
void Transform::Init(const Transform& t)
{
	this->pos = t.pos;
	this->rot = t.rot;
	this->scale = t.scale;
}

/**
* @brief 一つ一つ値で渡す移動
*/
void Transform::Move(const float x, const float y)
{
	pos.x += x;
	pos.y += y;
}
/**
* @brief　クラスで渡す移動
*/
void Transform::Move(const VEC2& _pos)
{
	pos += _pos;
}

/**
* @brief　回転
*/
void Transform::Rotate(const float _rot)
{
	rot += _rot;
}
/**
* @brief　拡大・縮小
*/
void Transform::Scaling(const float _scale)
{
	scale += _scale;
}
//オペレーターに関してはdoxygen省略
void Transform::operator=(const Transform& t)
{
	this->pos = t.pos; this->rot = t.rot; this->scale = t.scale;
}
void Transform::operator+=(const Transform& t)
{
	this->pos += t.pos; this->rot += t.rot; this->scale += t.scale;
}
void Transform::operator-=(const Transform& t)
{
	this->pos -= t.pos; this->rot -= t.rot; this->scale -= t.scale;
}
void Transform::operator*=(const Transform& t)
{
	this->pos *= t.pos; this->rot *= t.rot; this->scale *= t.scale;
}
void Transform::operator*=(const float s)
{
	this->pos *= s; this->rot *= s; this->scale *= s;
}
void Transform::operator/=(const float s)
{
	this->pos /= s; this->rot /= s; this->scale /= s;
}
Transform Transform::operator+(const Transform& t)const
{
	Transform _t(this->pos + t.pos, this->rot + t.rot, this->scale + t.scale);
	return _t;
}
Transform Transform::operator-(const Transform& t)const
{
	Transform _t(this->pos - t.pos, this->rot - t.rot, this->scale - t.scale);
	return _t;
}
bool Transform::operator==(const Transform& t)const
{
	return (this->pos == t.pos) && (this->rot == t.rot) && (this->scale == t.scale);
}
bool Transform::operator!=(const Transform& t)const
{
	return !(*this == t);
}