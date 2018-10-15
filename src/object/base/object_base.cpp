/**
* @file object_base.cpp
* @brief オブジェクトクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/11
*/
#include "object_base.h"

/**
* @brief 初期化
* @param name mapで管理するためのキー
* @param path テクスチャのパス
* @param w,h テクスチャのサイズ
* @param pos 初期位置
* @param rot 回転
* @param scale サイズ
* @param all_render テクスチャすべてを描画するかどうか
* @param テクスチャをすべて描画するかどうか
*/
void ObjectBase::Init(std::string name, WCHAR* path, const LONG w, const LONG h,
	VEC2 pos, float rot, float scale, bool all_render)
{
	transform.Init(pos, rot, scale);
	transform.size = VEC2(static_cast<float>(w), static_cast<float>(h));
	sprite.Init(name, path, all_render, w, h);
	InitProcess();
}

/**
* @brief 更新するかどうか決める
*/
void ObjectBase::Update()
{
	if (!enabled)return;
	UpdateProcess();
}

/**
* @brief 描画するかどうかを決める
* @param camera_affected カメラの位置によって描画位置を変えるかどうか
* @param t Transformクラス
*/
void ObjectBase::Render(bool camera_affected, const Transform& t)
{
	if (!enabled)return;
	worldTransform = t + transform;
	RenderProcess(camera_affected);
}