/**
* @file sprite.h
* @brief Sprite�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/19
*/
#pragma once
#include "../../transform/transform.h"
#include "manager/sprite_manager.h"

/**
* @brief �摜�̐F�̍\����
*/
struct SpriteColor
{
	float r, g, b, a;
	/**
	* @brief �R�s�[������Z�q
	*/
	SpriteColor& operator=(const SpriteColor& sc)
	{
		if (this != &sc)
		{
			this->r = sc.r;
			this->g = sc.g;
			this->b = sc.b;
			this->a = sc.a;
		}
		return *this;
	}
};
/**
* @brief �X�̉摜���Ǘ�����N���X
*/
class Sprite
{
	RECT rect;
	SpriteColor color;
	//map�ŊǗ����Ă��邽�ߎ����̖��O���K�v
	std::string my_name;
public:
	void Init(std::string name, WCHAR* path, const LONG w, const LONG h, 
		const float r = 1.0f, const float g = 1.0f, const float b = 1.0f, const float a = 1.0f);

	void Render(const Transform&, bool = true, bool = true, 
		const  DirectX::SpriteEffects = DirectX::SpriteEffects::SpriteEffects_None);
	/**
	* @brief �e�N�X�`���̕`�悷�镔����ς���i�A�j���[�V�����j
	* @param new_rect �V�����ʒu��rect
	*/
	void SetRect(const RECT& new_rect)
	{
		rect = new_rect;
	}
	Sprite() {}
	/**
	* @brief �R�s�[�R���X�g���N�^
	*/
	Sprite(const Sprite& s)
	{
		this->my_name = s.my_name;
		this->rect = s.rect;
		this->color = s.color;
	}
	/**
	* @brief �R�s�[������Z�q
	*/
	Sprite& operator=(const Sprite& other)
	{
		if (this != &other)
		{
			this->my_name = other.my_name;
			this->rect = other.rect;
			this->color = other.color;
		}
		return *this;
	}

	/**
	* @brief �F��ς���
	* @param r,g,b,a �F
	*/
	void ColorChange(const float r, const float g, const float b, const float a)
	{
		color.r = r; color.g = g; color.b = b; color.a = a;
	}
};