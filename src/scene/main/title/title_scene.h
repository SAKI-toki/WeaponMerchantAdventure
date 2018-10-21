/**
* @file title_scene.h
* @brief タイトルシーンクラスの宣言
* @author 石山　悠
* @date 2018/10/02
*/
#pragma once
#include "../../scene.h"
#include "../../../rendering/font/font.h"

/**
* @brief タイトルシーンクラス
*/
class TitleScene :public Scene
{
	Font font;
public:
	void Init()final;
	SCENE Update()final;
	void Render()final;
	void Destroy()final;
};