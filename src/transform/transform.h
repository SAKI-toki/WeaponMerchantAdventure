/**
* @file transform.h
* @brief transform�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/04
*/
#pragma once
#include <SimpleMath.h>
using VEC2 = DirectX::SimpleMath::Vector2;
using VEC3 = DirectX::SimpleMath::Vector3;

/**
* @transform�N���X
*/
class Transform
{
public:
	VEC2 pos;	//�ʒu
	VEC3 rot;	//��]
	VEC2 scale;	//�g��E�k��

	//�R���X�g���N�^
	Transform();
	Transform(const float, const float = 0, const float = 0, const float = 0, const float = 0, const float = 0, const float = 0);
	Transform(const VEC2& _pos, const VEC3& _rot, const VEC2& _scale);
	Transform(const Transform& t);

	//�ړ�
	void Move(const float, const float);
	void Move(const VEC2&);

	//��]
	void Rotate(const float, const float, const float);
	void Rotate(const VEC3&);

	//�g��E�k��
	void Scaling(const float, const float);
	void Scaling(const VEC2&);

	//���������揜�poperator
	void operator=(const Transform&);
	void operator+=(const Transform&);
	void operator-=(const Transform&);
	void operator*=(const Transform&);
	void operator*=(const float);
	void operator/=(const float);
	Transform operator+(const Transform&)const;
	Transform operator-(const Transform&)const;
	//��r�poperator
	bool operator==(const Transform&)const;
	bool operator!=(const Transform&)const;


};