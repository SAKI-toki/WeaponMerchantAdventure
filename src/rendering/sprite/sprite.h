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
	/**
	* @brief コピー代入演算子
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
* @brief 個々の画像を管理するクラス
*/
class Sprite
{
	RECT rect;
	SpriteColor color;
	//mapで管理しているため自分の名前が必要
	std::string my_name;
public:
	void Init(std::string name, WCHAR* path, const LONG w, const LONG h, 
		const float r = 1.0f, const float g = 1.0f, const float b = 1.0f, const float a = 1.0f);

	void Render(const Transform&, bool = true, bool = true, 
		const  DirectX::SpriteEffects = DirectX::SpriteEffects::SpriteEffects_None);
	/**
	* @brief テクスチャの描画する部分を変える（アニメーション）
	* @param new_rect 新しい位置のrect
	*/
	void SetRect(const RECT& new_rect)
	{
		rect = new_rect;
	}
	Sprite() {}
	/**
	* @brief コピーコンストラクタ
	*/
	Sprite(const Sprite& s)
	{
		this->my_name = s.my_name;
		this->rect = s.rect;
		this->color = s.color;
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
		}
		return *this;
	}

	/**
	* @brief 色を変える
	* @param r,g,b,a 色
	*/
	void ColorChange(const float r, const float g, const float b, const float a)
	{
		color.r = r; color.g = g; color.b = b; color.a = a;
	}
};