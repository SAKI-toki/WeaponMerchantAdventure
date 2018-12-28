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
	virtual void CollisionProcess(ObjectBase*, Vec2) {}
public:
	/**
	* @brief コンストラクタ
	*/
	StaticObject() :ObjectBase(false) {}
	StaticObject(const StaticObject& other) :ObjectBase(other)
	{
	}
	/**
	* @brief コピー代入演算子
	*/
	StaticObject& operator=(const StaticObject& other)
	{
		if (this != &other)
		{
			ObjectBase::operator=(other);
		}
		return *this;
	}
	virtual void Destroy(){}
	virtual void Collision(ObjectBase*, Vec2) {}
	
	virtual ~StaticObject() {}

	void SetColor(const float, const float, const float, const float);
};