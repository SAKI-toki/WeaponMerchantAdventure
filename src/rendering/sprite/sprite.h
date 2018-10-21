/**
* @file sprite.h
* @brief Spriteクラスの宣言
* @author 石山　悠
* @date 2018/10/19
*/
#pragma once
#include "../../transform/transform.h"
#include "manager/sprite_manager.h"

/**
* @brief 画像の色の構造体
*/
struct SpriteColor
{
	float r, g, b, a;
};
/**
* @brief 個々の画像を管理するクラス
*/
class Sprite
{
	RECT rect;
	SpriteColor color;
	//テクスチャ1枚すべてを描画する場合true
	bool all_render;
	//mapで管理しているため自分の名前が必要
	std::string my_name;
public:
	void Init(std::string name, WCHAR* path, const bool _all_render, const LONG w, const LONG h, const float r = 1.0f, const float g = 1.0f, const float b = 1.0f, const float a = 1.0f);
	void Render(const Transform&, bool = true, bool = true);
	Sprite() {}
	/**
	* @brief コピーコンストラクタ
	*/
	Sprite(const Sprite& s)
	{
		this->my_name = s.my_name;
		this->rect = s.rect;
		this->color = s.color;
		this->all_render = s.all_render;
	}
	/**
	* @brief コピー代入演算子
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