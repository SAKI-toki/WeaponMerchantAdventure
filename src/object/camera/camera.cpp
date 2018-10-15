/**
* @file camera.cpp
* @brief カメラクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/09
*/
#include "camera.h"
#include "../../common/common.h"

/**
* @brief カメラのゼロ初期化コンストラクタ
*/
Camera::Camera() :
	camera_pos(VEC2::Zero)
{}
/**
* @brief カメラの値を受け取る初期化コンストラクタ
* @param v2 初期化する値
*/
Camera::Camera(const VEC2& v2):
	camera_pos(v2)
{}

/**
* @brief カメラの移動
* @param v2 移動量
*/
void Camera::Move(const VEC2& v2)
{
	camera_pos += v2;
}
/**
* @brief カメラの位置変更
* @param v2 位置
*/
void Camera::SetPos(const VEC2& v2)
{
	camera_pos = v2 - VEC2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
}

/**
* @brief カメラの位置を取得
* @return VEC2:カメラの位置
*/
VEC2 Camera::GetPos()const
{
	return camera_pos;
}

/**
* @brief カメラの更新
*/
void Camera::Update()
{
	SetPos(target->transform.pos);
}