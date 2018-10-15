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
	WCHAR* text;
	const Transform& transform;
	FontColor color;
public:
	//デフォルトコンストラクタ削除
	Font() = delete;

	Font(const Transform&);

	void Init(WCHAR* _text, float r = 1, float g = 1, float b = 1, float a = 1);
	void Render();

	/**
	* @brief 文字列のセット
	* @param _text セットする文字列
	*/
	void SetText(WCHAR* _text) { text = _text; }
	/**
	* @brief テキストを取得する
	* @return WCHAR* テキスト
	*/
	WCHAR* GetText() { return text; }
};