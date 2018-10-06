/**
* @file transform.cpp
* @brief transform�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/06
*/
#include "transform.h"

/**
* :brief�@�[���ŏ�������������Ȃ��R���X�g���N�^
*/
Transform::Transform() :
	pos(VEC2::Zero), rot(0.0f), scale(1.0f)
{}
/**
* @brief pos�����ꂼ��̃p�����[�^�Ŏ󂯎��R���X�g���N�^
*/
Transform::Transform(const float posx, const float posy, const float _rot, const float _scale):
	pos(VEC2(posx,posy)),rot(_rot),scale(_scale)
{}
/**
* @brief pos��VEC2�N���X�Ŏ󂯎��R���X�g���N�^
*/
Transform::Transform(const VEC2& _pos, const float _rot, const float _scale):
	pos(_pos),rot(_rot),scale(_scale)
{}
/**
* @brief �R�s�[�R���X�g���N�^
*/
Transform::Transform(const Transform& t)
{
	this->Init(t);
}
/**
* @brief ���l�œn��������
*/
void Transform::Init(const float posx, const  float posy, const float _rot, const  float _scale)
{
	pos = { posx,posy };
	rot = _rot;
	scale = _scale;
}
/**
* @brief �e�N���X�ɑ΂��Ēl��n��������
*/
void Transform::Init(const VEC2& _pos, const float _rot, const float _scale)
{
	pos = _pos;
	rot = _rot;
	scale = _scale;
}
/**
* @brief Transform�N���X��n��������
*/
void Transform::Init(const Transform& t)
{
	this->pos = t.pos;
	this->rot = t.rot;
	this->scale = t.scale;
}

/**
* @brief ���l�œn���ړ�
*/
void Transform::Move(const float x, const float y)
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
* @brief�@��]
*/
void Transform::Rotate(const float _rot)
{
	rot += _rot;
}
/**
* @brief�@�g��E�k��
*/
void Transform::Scaling(const float _scale)
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