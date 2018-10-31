/**
* @file game_clear.h
* @brief ゲームクリアクラスの宣言
* @author 石山　悠
* @date 2018/10/29
*/
#pragma once
#include "../../scene.h"
/**
* @brief ゲームクリアクラス
*/
class GameClearScene :public Scene
{
public:
	void Init()final;
	SCENE Update()final;
	void Render()final;
	void Destroy()final;
};