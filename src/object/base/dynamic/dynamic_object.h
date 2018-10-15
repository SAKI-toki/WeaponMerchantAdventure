/**
* @file dynamic_object.h
* @brief 動くオブジェクトのスーパークラスの宣言
* @author 石山　悠
* @date 2018/10/04
*/
#pragma once
#include "../object_base.h"

/**
* @brief 動くオブジェクトのスーパークラス
*/
class DynamicObject :public ObjectBase
{
protected:
	void RenderProcess(bool);
public:
	virtual ~DynamicObject() {}
};