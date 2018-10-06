/**
* @file player.h
* @brief プレイヤークラスを宣言
* @author 石山　悠
* @date 2018/10/07
*/
#pragma once
#include "../base/character_base.h"

/**
* @brief プレイヤークラス
*/
class Player :public CharacterBase
{
public:
	HRESULT Init(WCHAR* path, const LONG w, const LONG h, VEC2 pos, float rot = 0, float scale = 1)final;
	void Update()final;
	void Render()final;
	void Destroy()final;
};