/**
* @file sprite.cpp
* @brief Spriteクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/10/04
*/
#include "sprite.h"
#include "../../../DeviceResources.h"
#include "../../../Main.h"
#include <WICTextureLoader.h>

/**
* @brief 各パラメータや画像を読み込む
* @param path テクスチャのパス
* @param h,w　テクスチャの大きさ
* @param r,g,b,a 色
*/
void Sprite::Init(WCHAR* path, const int h, const int w, float r, float g, float b, float a)
{
	height = h; width = w;
	color.r = r; color.g = g; color.b = b; color.a = a;
	//テクスチャを取得
	texture = SpriteManager::GetInstance()->GetTexture(path);
}

/**
* @brief SpriteBatchを経由して描画する
* @param t 位置や回転、拡大・縮小のクラス
*/
void Sprite::Render(const Transform& t)
{
	//メンバ変数にするとアライメントがどうのこうのと言われるのでここで変換
	DirectX::XMVECTOR _color = DirectX::XMVectorSet(color.r, color.g, color.b, color.a);
	//描画
	SpriteManager::GetInstance()->GetSpriteBatch()->Draw(texture.Get(), t.pos, nullptr, _color, 0.0f, t.pos);
}