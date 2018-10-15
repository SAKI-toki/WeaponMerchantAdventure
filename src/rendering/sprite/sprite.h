/**
* @file sprite.h
* @brief Sprite�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/11
*/
#pragma once
#include "../../transform/transform.h"
#include "manager/sprite_manager.h"


struct SpriteColor
{
	float r, g, b, a;
};
/**
* @brief �X�̉摜���Ǘ�����N���X
*/
class Sprite
{
	CP<ID3D11ShaderResourceView> texture;
	RECT rect;
	SpriteColor color;
	//�e�N�X�`��1�����ׂĂ�`�悷��ꍇtrue
	bool all_render;
public:
	void Init(std::string name, WCHAR* path, const bool _all_render, const LONG w, const LONG h, const float r = 1.0f, const float g = 1.0f, const float b = 1.0f, const float a = 1.0f);
	void Render(const Transform&, bool = true);
};