/**
* @file static_object.h
* @brief 動かないオブジェクトのスーパークラスの宣言
* @author 石山　悠
* @date 2018/10/04
*/
#pragma once
#include "../object_base.h"
/**
* @brief 動かないオブジェクトのスーパークラス
*/
class StaticObject :public ObjectBase
{
protected:
	void RenderProcess(bool);
	virtual void InitProcess() {}
	virtual void UpdateProcess() {}
	virtual void CollisionProcess(ObjectBase*,VEC2) {}
public:
	virtual void Destroy(){}
	virtual void Collision(ObjectBase*, VEC2) {}
	
	virtual ~StaticObject() {}
};