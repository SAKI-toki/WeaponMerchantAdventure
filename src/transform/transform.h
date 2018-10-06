/**
* @file transform.h
* @brief transform�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/06
*/
#pragma once
#include <SimpleMath.h>
using VEC2 = DirectX::SimpleMath::Vector2;

/**
* @transform�N���X
*/
class Transform
{
public:
	VEC2 pos;	//�ʒu
	float rot;	//��]
	float scale;//�g��E�k��

	//�R���X�g���N�^
	Transform();
	Transform(const float, const float = 0, const float = 0, const float = 1);
	Transform(const VEC2& _pos, const float _rot, const float _scale);
	//�R�s�[�R���X�g���N�^
	Transform(const Transform& t);
	//������
	void Init(const float, const float = 0, const float = 0, const float = 1);
	void Init(const VEC2& _pos, const float _rot, const float _scale);
	void Init(const Transform& t);

	//�ړ�
	void Move(const float, const float);
	void Move(const VEC2&);

	//��]
	void Rotate(const float);

	//�g��E�k��
	void Scaling(const float);

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