/**
* @file object_base.cpp
* @brief オブジェクトクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/11
*/
#include "object_base.h"

/**
* @brief 初期化
* @param name テクスチャをロードするためのキー
* @param path テクスチャのパス
* @param w,h テクスチャのサイズ
* @param pos 初期位置
* @param rot 回転
* @param scale 拡大・縮小
* @param テクスチャをすべて描画するかどうか
*/
void ObjectBase::Init(std::string name, WCHAR* path, const float w, const float h,
	Vec3 pos, Vec3 rot, Vec3 scale)
{
	transform.set_pos(pos);
	transform.set_rot(rot);
	transform.set_scale(scale);
	size.x = w, size.y = h;
	sprite.Init(name, path, Vec2(w, h));
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
//#define COLLIDER_DEBUG
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
#if defined(_DEBUG) && defined(COLLIDER_DEBUG)
	static Sprite debug_sprite;
	static bool first = true;
	if (std::exchange(first, false))
	{
		debug_sprite.Init("ColliderDebug", L"collider_debug.png", Vec2(1, 1));
	}
	debug_sprite.ColorChange(0.0f, 1.0f, 0.0f, 0.8f);
	debug_sprite.Render(Transform{
			transform.get_pos() + Vec3{0,0,-1},
			saki::vector3_zero<float>,
			transform.get_scale()*Vec3(size.x,size.y,1)*DebugCollisionScale()
		});
#endif
}