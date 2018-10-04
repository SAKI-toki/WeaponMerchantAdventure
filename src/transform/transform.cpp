/**
* @file transform.cpp
* @brief transform�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/04
*/
#include "transform.h"

/**
* :brief�@�[���ŏ�������������Ȃ��R���X�g���N�^
*/
Transform::Transform() :
	pos(VEC2::Zero), rot(VEC3::Zero), scale(VEC2::Zero)
{}
/**
* @brief ���l�œn���R���X�g���N�^
*/
Transform::Transform(const float posx, const  float posy, const float rotx, const float roty, const float rotz, const  float scalex, const float scaley)
{
	pos = { posx,posy };
	rot = { rotx,roty,rotz };
	scale = { scalex,scaley };
}
/**
* @brief �e�N���X�ɑ΂��Ēl��n���R���X�g���N�^
*/
Transform::Transform(const VEC2& _pos, const VEC3& _rot, const VEC2& _scale) :
	pos(_pos), rot(_rot), scale(_scale) {}
/**
* @brief Transform�N���X��n���R���X�g���N�^
*/
Transform::Transform(const Transform& t) :
	pos(t.pos), rot(t.rot), scale(t.scale) {}

/**
* @brief ���l�œn���ړ�
*/
void Transform::Move(const float x = 0, const float y = 0)
{
	pos.x += x;
	pos.y += y;
}
/**
* @brief�@�N���X�œn���ړ�
*/
void Transform::Move(const VEC2& _pos)
{
	pos += _pos;
}

/**
* @brief�@���l�œn����]
*/
void Transform::Rotate(const float x = 0, const float y = 0, const  float z = 0)
{
	rot.x += x;
	rot.y += y;
	rot.z += z;
}
/**
* @brief�@�N���X�œn����]
*/
void Transform::Rotate(const VEC3& _rot)
{
	rot += _rot;
}

/**
* @brief�@���l�œn���g��E�k��
*/
void Transform::Scaling(const float x = 0, const  float y = 0)
{
	scale.x += x;
	scale.y += y;
}
/**
* @brief�@�N���X�œn���g��E�k��
*/
void Transform::Scaling(const VEC2& _scale)
{
	scale += _scale;
}

//�I�y���[�^�[�Ɋւ��Ă�doxygen�ȗ�
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