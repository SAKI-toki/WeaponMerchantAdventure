/**
* @file sprite.cpp
* @brief Sprite�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/04
*/
#pragma once
#include <SpriteBatch.h>
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
	CP<ID3D11ShaderResourceView> texture;
	int height, width;
	Color color;
public:
	void Init(WCHAR*, const int h, const int w, float = 1.0f, float = 1.0f, float = 1.0f, float = 1.0f);
	void Render(const Transform&);
};