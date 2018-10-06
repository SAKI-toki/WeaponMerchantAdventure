/**
* @file object_base.h
* @brief オブジェクトのスーパークラスを宣言
* @author 石山　悠
* @date 2018/10/05
*/
#pragma once
#include <winnt.h>//for HRESULT
#include "../../transform/transform.h"
#include "../../rendering/sprite/sprite.h"

/**
* @brief オブジェクトのスーパークラス
*/
class ObjectBase
{
public:
	Transform transform; //位置、回転、拡大・縮小
	virtual ~ObjectBase() {}
};