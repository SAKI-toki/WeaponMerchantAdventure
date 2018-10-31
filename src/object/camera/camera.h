/**
* @file camera.h
* @brief カメラクラスを宣言
* @author 石山　悠
* @date 2018/10/09
*/
#pragma once
#include "../../common/singleton.h"
#include "../../transform/transform.h"
#include "../base/object_base.h"


/**
* @brief カメラクラス
*/
class Camera :public Singleton<Camera>
{
	//カメラの位置
	VEC2 camera_pos = VEC2::Zero;
	//追尾させるターゲット
	ObjectBase* target = nullptr;
public:
	Camera() {}
	Camera(const VEC2&);
	void Move(const VEC2&);
	void SetPos(const VEC2&);
	VEC2 GetPos()const;
	void Update();
	/**
	* brief ターゲットのセット
	*/
	void SetTarget(ObjectBase* t)
	{
		target = t;
	}
};