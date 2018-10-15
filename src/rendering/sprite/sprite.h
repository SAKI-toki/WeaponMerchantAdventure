/**
* @file sprite.h
* @brief Spriteクラスの宣言
* @author 石山　悠
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
* @brief 個々の画像を管理するクラス
*/
class Sprite
{
	CP<ID3D11ShaderResourceView> texture;
	RECT rect;
	SpriteColor color;
	//テクスチャ1枚すべてを描画する場合true
	bool all_render;
public:
	void Init(std::string name, WCHAR* path, const bool _all_render, const LONG w, const LONG h, const float r = 1.0f, const float g = 1.0f, const float b = 1.0f, const float a = 1.0f);
	void Render(const Transform&, bool = true);
};