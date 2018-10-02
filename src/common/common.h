/**
* @file common.h
* @brief 定数定義やヘッダのインクルード
* @author 石山　悠
* @date 2018/10/02
*/
#pragma once
#include <windows.h>

namespace
{
	//定数定義
	inline constexpr bool FULL_SCREEN = false;
	inline constexpr int WINDOW_WIDTH = 1920;
	inline constexpr int WINDOW_HEIGHT = 1080;
	inline constexpr float STICK_DEAD_ZONE = 0.3f;
	inline constexpr float TRIGGER_DEAD_ZONE = 0.3f;
	inline constexpr int MAX_CONTROLLERS = 1;
}