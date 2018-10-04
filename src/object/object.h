/**
* @file object.h
* @brief オブジェクトのスーパークラスを宣言
* @author 石山　悠
* @date 2018/10/04
*/
#pragma once
#include <winnt.h>//for HRESULT

/**
* @brief オブジェクトのスーパークラス
*/
class Object
{
public:
	virtual ~Object() {}

	virtual HRESULT Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
};