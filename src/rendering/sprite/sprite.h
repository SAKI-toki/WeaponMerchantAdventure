/**
* @file sprite.cpp
* @brief SpriteNXΜιΎ
* @author ΞR@I
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
* @brief ΒXΜζπΗ·ιNX
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