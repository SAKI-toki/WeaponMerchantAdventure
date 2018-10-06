/**
* @file character.h
* @brief Characterスーパークラスを宣言
* @author 石山　悠
* @date 2018/10/07
*/
#pragma once
#include "../../base/object_base.h"

/**
* @brief キャラクター関係のスーパークラス
*/
class CharacterBase :public ObjectBase
{
protected:
	//TODO:Add Animation,Collider
	Sprite sprite;
	bool enabled;
public:
	CharacterBase();
	virtual ~CharacterBase() {}
	virtual HRESULT Init(WCHAR* path, const LONG w, const LONG h, VEC2 pos, float rot, float scale) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
};