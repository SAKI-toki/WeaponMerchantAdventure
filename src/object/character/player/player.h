/**
* @file player.h
* @brief �v���C���[�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/07
*/
#pragma once
#include "../base/character_base.h"

/**
* @brief �v���C���[�N���X
*/
class Player :public CharacterBase
{
public:
	HRESULT Init(WCHAR* path, const LONG w, const LONG h, VEC2 pos, float rot = 0, float scale = 1)final;
	void Update()final;
	void Render()final;
	void Destroy()final;
};