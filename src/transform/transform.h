/**
* @file transform.h
* @brief transform�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/09
*/
#pragma once
#include "../common/common.h"
#include <SpriteBatch.h>

/**
* @brief transform�N���X
*/
class Transform
{
public:
	VEC2 pos = VEC2::Zero;	//�ʒu
	float rot = 0.0f;	//��]
	float scale = 0.0f;//�g��E�k��
	VEC2 size = VEC2::Zero;//�T�C�Y
	DirectX::SpriteEffects sprite_effect;//���]

	//�R���X�g���N�^
	Transform() {}
	Transform(const float, const float = 0, const float = 0, const float = 1, const float = 0, const float = 0, const DirectX::SpriteEffects = DirectX::SpriteEffects_None);
	Transform(const VEC2& _pos, const float _rot, const float _scale, const VEC2& = VEC2::Zero, const DirectX::SpriteEffects = DirectX::SpriteEffects_None);

	//�R�s�[�R���X�g���N�^
	Transform(const Transform& t);

	//������
	void Init(const float, const float = 0, const float = 0, const float = 1, const float = 0, const float = 0, const DirectX::SpriteEffects = DirectX::SpriteEffects_None);
	void Init(const VEC2& _pos, const float _rot = 0, const float _scale = 0, const VEC2& = VEC2::Zero, const DirectX::SpriteEffects = DirectX::SpriteEffects_None);
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