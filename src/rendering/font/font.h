/**
* @file font.h
* @brief フォントクラスを宣言
* @author 石山　悠
* @date 2018/10/09
*/
#pragma once
#include "manager/font_manager.h"
#include "../../transform/transform.h"
/**
* @brief フォント用の色構造体
*/
struct FontColor
{
	float r, g, b, a;
};

/**
* @brief フォントクラス
*/
class Font
{
	WCHAR text[100];
	Transform transform;
	FontColor color;
public:

	void Init(WCHAR* _text, float r = 0, float g = 0, float b = 0, float a = 1);
	void Render();

	/**
	* @brief 文字列のセット
	* @param _text セットする文字列
	*/
	void SetText(WCHAR* _text) { wcscpy_s(text, _text); }
	/**
	* @brief テキストを取得する
	* @return WCHAR* テキスト
	*/
	WCHAR* GetText() { return text; }

	/**
	* @brief 位置をセット
	* @return t 位置や回転等を含む
	*/
	void SetTransform(const Transform& t) { transform = t; }
	/**
	* @brief 色を変える
	* @param r,g,b,a 色
	*/
	void ColorChange(const float r, const float g, const float b, const float a)
	{
		color.r = r; color.g = g; color.b = b; color.a = a;
	}
};