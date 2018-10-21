/**
* @file sprite.cpp
* @brief Spriteクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/10/19
*/
#include "sprite.h"
#include "../../../DeviceResources.h"
#include "../../../Main.h"
#include <WICTextureLoader.h>
#include <SpriteBatch.h>
#include "../../object/camera/camera.h"

/**
* @brief 各パラメータや画像を読み込む
* @param name mapで管理するためのキー
* @param path テクスチャのパス
* @param h,w　テクスチャの大きさ
* @param _all_render テクスチャをすべて描画するかどうか（アニメーションがあるかどうかとほぼ同義）
* @param r,g,b,a 色
*/
void Sprite::Init(std::string name, WCHAR* path, const bool _all_render, const LONG w, const LONG h, const float r, const float g, const float b, const float a)
{
	//テクスチャのサイズを代入
	rect = { 0,0,w,h };
	my_name = name;
	//すべて描画するかどうか
	all_render = _all_render;
	color.r = r; color.g = g; color.b = b; color.a = a;
	//テクスチャをセット
	SpriteManager::GetInstance()->SetTexture(name, path);
}

/**
* @brief SpriteBatchを経由して描画する
* @param transform 位置や回転、拡大・縮小
* @param affected_camera カメラの位置によって描画する位置を変えるかどうか
*/
void Sprite::Render(const Transform& transform, bool affected_camera, bool center_axis)
{

	/*try {
		//描画
		if (affected_camera)
		{
			SpriteManager::GetInstance()->GetSpriteBatch()->Draw(texture.Get(), transform.pos - Camera::GetInstance()->GetPos(), &rect, _color, transform.rot, { (center_axis)?rect.right / 2.0f:0.0f,(center_axis) ? rect.bottom / 2.0f : 0.0f }, transform.scale);
		}
		else
		{
			SpriteManager::GetInstance()->GetSpriteBatch()->Draw(texture.Get(), transform.pos, &rect, _color, transform.rot, { (center_axis) ? rect.right / 2.0f : 0.0f,(center_axis) ? rect.bottom / 2.0f : 0.0f }, transform.scale);
		}
	}
	catch (std::exception& e)
	{
		WCHAR str[100];
		auto s = e.what();
		size_t len = 0;
		mbstowcs_s(&len, str, 50, s, _TRUNCATE);
		Comment(str, L"");
	}*/
	//メンバ変数にするとアライメントがどうのこうのと言われるのでここで変換
	DirectX::XMVECTOR _color = DirectX::XMVectorSet(color.r, color.g, color.b, color.a);
	SpriteManager::GetInstance()->Render(transform, affected_camera, center_axis, my_name, _color, rect);
}