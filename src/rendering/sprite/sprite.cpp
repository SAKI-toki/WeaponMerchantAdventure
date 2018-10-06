/**
* @file sprite.cpp
* @brief Spriteクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/10/06
*/
#include "sprite.h"
#include "../../../DeviceResources.h"
#include "../../../Main.h"
#include <WICTextureLoader.h>
#include <SpriteBatch.h>

/**
* @brief Transformクラスを受け取るコンストラクタ
* @param t Transformクラス
*/
Sprite::Sprite(const Transform& t) :
	transform(t) {}
/**
* @brief 各パラメータや画像を読み込む
* @param path テクスチャのパス
* @param h,w　テクスチャの大きさ
* @param _all_render テクスチャをすべて描画するかどうか（アニメーションがあるかどうかとほぼ同義）
* @param r,g,b,a 色
*/
void Sprite::Init(WCHAR* path, const bool _all_render, const LONG w, const LONG h, const float r, const float g, const float b, const float a)
{
	rect = { 0,0,w,h };
	all_render = _all_render;
	color.r = r; color.g = g; color.b = b; color.a = a;
	//テクスチャを取得
	texture = SpriteManager::GetInstance()->GetTexture(path);
}

/**
* @brief SpriteBatchを経由して描画する
*/
void Sprite::Render()
{
	//メンバ変数にするとアライメントがどうのこうのと言われるのでここで変換
	DirectX::XMVECTOR _color = DirectX::XMVectorSet(color.r, color.g, color.b, color.a);
	//描画
	SpriteManager::GetInstance()->GetSpriteBatch()->Draw(texture.Get(), transform.pos, &rect, _color, transform.rot, { rect.right / 2.0f,rect.bottom / 2.0f }, transform.scale);
}