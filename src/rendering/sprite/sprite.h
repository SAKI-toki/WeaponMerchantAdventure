/**
* @file sprite.cpp
* @brief Sprite�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/06
*/
#pragma once
#include "../../transform/transform.h"
#include "manager/sprite_manager.h"


struct Color
{
	float r, g, b, a;
};
/**
* @brief �X�̉摜���Ǘ�����N���X
*/
class Sprite
{
	const Transform& transform;
	CP<ID3D11ShaderResourceView> texture;
	RECT rect;
	Color color;
	//�e�N�X�`��1�����ׂĂ�`�悷��ꍇtrue
	bool all_render;
public:
	Sprite(const Transform&);
	void Init(WCHAR* path, const bool _all_render, const LONG w, const LONG h, const float r=1.0f, const float g = 1.0f, const float b = 1.0f, const float a = 1.0f);
	void Render(/*Animation anim =nullptr*/);
};