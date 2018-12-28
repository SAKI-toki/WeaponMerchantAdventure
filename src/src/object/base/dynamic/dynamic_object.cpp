/**
* @file dynamic_object.cpp
* @brief 動くオブジェクトのスーパークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/04
*/
#include "dynamic_object.h"

/**
* @brief 描画
* @param camera_affected カメラの位置によって位置を変えるかどうか
*/
void DynamicObject::RenderProcess(bool camera_affected)
{
	sprite.Render(transform, camera_affected);
}