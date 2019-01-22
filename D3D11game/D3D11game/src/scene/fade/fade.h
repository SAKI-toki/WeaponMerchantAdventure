/**
* @file fade.h
* @brief フェードクラスの宣言
* @author 石山　悠
* @date 2018/10/30
*/
#pragma once
#include "../../common/common.h"
#include "../../sprite/sprite.h"
#include <saki/singleton/singleton.h>



/**
* @brief フェードクラス
*/
class Fade :public saki::Singleton<Fade>
{
	//アルファ値
	float alpha = 0.0f;
	//黒のテクスチャ
	Sprite black;
	Transform transform;
public:
	void Init();
	bool Update(const bool);
	void Render();
	void Destroy();
};