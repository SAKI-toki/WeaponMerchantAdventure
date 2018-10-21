/**
* @file font.cpp
* @brief フォントクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/09
*/
#include "font.h"
#include "../sprite/manager/sprite_manager.h"

/**
* @brief 初期化
* @param _text テキスト
* @param r,g,b,a 色
*/
void Font::Init(WCHAR* _text, float r, float g, float b, float a)
{
	SetText(_text);
	color.r = r; color.g = g; color.b = b; color.a = a;
}

/**
* @brief 描画
*/
void Font::Render()
{

	//メンバ変数にするとアライメントがどうのこうのと言われるのでここで変換
	DirectX::XMVECTOR _color = DirectX::XMVectorSet(color.r, color.g, color.b, color.a);
	//描画
	FontManager::GetInstance()->GetSpriteFont()->DrawString(SpriteManager::GetInstance()->GetSpriteBatch().get(),
		text, transform.pos, _color, transform.rot, { 0,0 }, transform.scale);
}