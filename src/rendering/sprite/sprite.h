/**
* @file sprite.cpp
* @brief Spriteクラスの宣言
* @author 石山　悠
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
* @brief 個々の画像を管理するクラス
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