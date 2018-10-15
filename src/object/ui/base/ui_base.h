#pragma once
#include "../../base/dynamic/dynamic_object.h"

class UiBase :public DynamicObject
{
public:
	//ポリモーフィズムを利用するときはデストラクタは仮想関数にする
	virtual ~UiBase() {}
};