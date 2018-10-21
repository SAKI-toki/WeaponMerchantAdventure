/**
* @file transform.cpp
* @brief transform�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/06
*/
#include "transform.h"

/**
* @brief pos�����ꂼ��̃p�����[�^�Ŏ󂯎��R���X�g���N�^
*/
Transform::Transform(const float posx, const float posy, const float _rot, const float _scale, const float sizex, const float sizey) :
	pos(VEC2(posx, posy)), rot(_rot), scale(_scale), size(VEC2(sizex, sizey))
{}
/**
* @brief pos��VEC2�N���X�Ŏ󂯎��R���X�g���N�^
*/
Transform::Transform(const VEC2& _pos, const float _rot, const float _scale, const VEC2& _size) :
	pos(_pos), rot(_rot), scale(_scale), size(_size)
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
void Transform::Init(const float posx, const  float posy, const float _rot, const  float _scale,const float sizex,const float sizey)
{
	pos = { posx,posy };
	rot = _rot;
	scale = _scale;
	size = { sizex,sizey };
}
/**
* @brief �e�N���X�ɑ΂��Ēl��n��������
*/
void Transform::Init(const VEC2& _pos, const float _rot, const float _scale,const VEC2& _size)
{
	pos = _pos;
	rot = _rot;
	scale = _scale;
	size = _size;
}
/**
* @brief Transform�N���X��n��������
*/
void Transform::Init(const Transform& t)
{
	this->pos = t.pos;
	this->rot = t.rot;
	this->scale = t.scale;
	this->size = t.size;
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
	this->pos = t.pos; this->rot = t.rot; this->scale = t.scale; this->size = t.size;
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
	return (this->pos == t.pos) && (this->rot == t.rot) && (this->scale == t.scale) && (this->size == t.size);
}
bool Transform::operator!=(const Transform& t)const
{
	return !(*this == t);
}