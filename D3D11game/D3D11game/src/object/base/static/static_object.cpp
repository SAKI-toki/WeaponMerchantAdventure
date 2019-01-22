/**
* @file static_object.cpp
* @brief 動かないオブジェクトのスーパークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/04
*/
#include "static_object.h"

/**
* @brief 描画
* @param camera_affected カメラの位置によって位置を変えるかどうか
*/
void StaticObject::RenderProcess(bool camera_affected)
{
	sprite.Render(transform, camera_affected);
}

void StaticObject::SetColor(const float r, const float g, const float b, const float a)
{
	sprite.ColorChange(r, g, b, a);
}

