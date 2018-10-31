/**
* @file transform.cpp
* @brief transformクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/06
*/
#include "transform.h"

/**
* @brief posをそれぞれのパラメータで受け取るコンストラクタ
*/
Transform::Transform(const float posx, const float posy, const float _rot, const float _scale, const float sizex, const float sizey, const DirectX::SpriteEffects _sprite_effect) :
	pos(VEC2(posx, posy)), rot(_rot), scale(_scale), size(VEC2(sizex, sizey)), sprite_effect(_sprite_effect)
{}
/**
* @brief posをVEC2クラスで受け取るコンストラクタ
*/
Transform::Transform(const VEC2& _pos, const float _rot, const float _scale, const VEC2& _size, const DirectX::SpriteEffects _sprite_effect) :
	pos(_pos), rot(_rot), scale(_scale), size(_size), sprite_effect(_sprite_effect)
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
void Transform::Init(const float posx, const  float posy, const float _rot, const  float _scale,const float sizex,const float sizey, const DirectX::SpriteEffects _sprite_effect)
{
	pos = { posx,posy };
	rot = _rot;
	scale = _scale;
	size = { sizex,sizey };
	sprite_effect = _sprite_effect;
}
/**
* @brief 各クラスに対して値を渡す初期化
*/
void Transform::Init(const VEC2& _pos, const float _rot, const float _scale,const VEC2& _size, const DirectX::SpriteEffects _sprite_effect)
{
	pos = _pos;
	rot = _rot;
	scale = _scale;
	size = _size;
	sprite_effect = _sprite_effect;
}
/**
* @brief Transformクラスを渡す初期化
*/
void Transform::Init(const Transform& t)
{
	this->pos = t.pos;
	this->rot = t.rot;
	this->scale = t.scale;
	this->size = t.size;
	this->sprite_effect = t.sprite_effect;
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
	this->pos = t.pos; this->rot = t.rot; this->scale = t.scale; this->size = t.size; this->sprite_effect = t.sprite_effect;
}
void Transform::operator+=(const Transform& t)
{
	this->pos += t.pos; this->rot += t.rot; this->scale += t.scale; this->size += t.size; 
}
void Transform::operator-=(const Transform& t)
{
	this->pos -= t.pos; this->rot -= t.rot; this->scale -= t.scale; this->size -= t.size;
}
void Transform::operator*=(const Transform& t)
{
	this->pos *= t.pos; this->rot *= t.rot; this->scale *= t.scale; this->size *= t.size;
}
void Transform::operator*=(const float s)
{
	this->pos *= s; this->rot *= s; this->scale *= s; this->size *= s;
}
void Transform::operator/=(const float s)
{
	this->pos /= s; this->rot /= s; this->scale /= s; this->size /= s;
}
Transform Transform::operator+(const Transform& t)const
{
	Transform _t(this->pos + t.pos, this->rot + t.rot, this->scale + t.scale, this->size + t.size);
	return _t;
}
Transform Transform::operator-(const Transform& t)const
{
	Transform _t(this->pos - t.pos, this->rot - t.rot, this->scale - t.scale, this->size - t.size);
	return _t;
}
bool Transform::operator==(const Transform& t)const
{
	return (this->pos == t.pos) && (this->rot == t.rot) && (this->scale == t.scale) && (this->size == t.size) && (this->sprite_effect == t.sprite_effect);
}
bool Transform::operator!=(const Transform& t)const
{
	return !(*this == t);
}