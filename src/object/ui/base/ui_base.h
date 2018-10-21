/**
* @file ui_base.h
* @brief uiのスーパークラスを宣言
* @author 石山　悠
* @date 2018/10/15
*/
#pragma once
#include "../../base/dynamic/dynamic_object.h"

/**
* @brief uiのスーパークラス
*/
class UiBase :public DynamicObject
{
public:
	//ポリモーフィズムを利用するときはデストラクタは仮想関数にする
	virtual ~UiBase() {}
};