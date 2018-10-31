/**
* @file fade.h
* @brief フェードクラスの宣言
* @author 石山　悠
* @date 2018/10/30
*/
#pragma once
#include "../../rendering/sprite/sprite.h"
#include "../../transform/transform.h"
#include "../../common/common.h"
#include "../../common/singleton.h"



/**
* @brief フェードクラス
*/
class Fade :public Singleton<Fade>
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