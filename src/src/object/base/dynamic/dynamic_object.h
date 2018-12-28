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
	virtual void RenderProcess(bool);
public:
	/**
	* @brief コンストラクタ
	*/
	DynamicObject() :ObjectBase(true) {}
	/**
	* @brief コピー代入演算子
	*/
	DynamicObject& operator=(const DynamicObject& other)
	{
		if (this != &other)
		{
			ObjectBase::operator=(other);
		}
		return *this;
	}
	virtual ~DynamicObject() {}
};