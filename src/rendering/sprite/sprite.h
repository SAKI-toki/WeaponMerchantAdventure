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
};
/**
* @brief �X�̉摜���Ǘ�����N���X
*/
class Sprite
{
	RECT rect;
	SpriteColor color;
	//�e�N�X�`��1�����ׂĂ�`�悷��ꍇtrue
	bool all_render;
	//map�ŊǗ����Ă��邽�ߎ����̖��O���K�v
	std::string my_name;
public:
	void Init(std::string name, WCHAR* path, const bool _all_render, const LONG w, const LONG h, const float r = 1.0f, const float g = 1.0f, const float b = 1.0f, const float a = 1.0f);
	void Render(const Transform&, bool = true, bool = true);
	Sprite() {}
	/**
	* @brief �R�s�[�R���X�g���N�^
	*/
	Sprite(const Sprite& s)
	{
		this->my_name = s.my_name;
		this->rect = s.rect;
		this->color = s.color;
		this->all_render = s.all_render;
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
			this->all_render = other.all_render;
		}
		return *this;
	}
};