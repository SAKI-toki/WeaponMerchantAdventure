/**
* @file select_scene.h
* @brief セレクトシーンクラスの宣言
* @author 石山　悠
* @date 2018/10/19
*/
#pragma once
#include "../../scene.h"
/**
* @brief セレクトシーンクラス
*/
class SelectScene :public Scene
{
public:
	void Init()final;
	SCENE Update()final;
	void Render()final;
	void Destroy()final;
};