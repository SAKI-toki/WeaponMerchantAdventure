/**
* @file game_over.h
* @brief ゲームオーバークラスの宣言
* @author 石山　悠
* @date 2018/10/29
*/
#pragma once
#include "../../scene.h"
class GameOverScene :public Scene
{
public:
	void Init()final;
	SCENE Update()final;
	void Render()final;
	void Destroy()final;
};