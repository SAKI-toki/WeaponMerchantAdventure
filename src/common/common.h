/**
* @file common.h
* @brief 定数定義やヘッダのインクルード
* @author 石山　悠
* @date 2018/10/07
*/
#pragma once
#include <windows.h>
#include <string>
namespace
{
	//定数定義
	inline constexpr bool FULL_SCREEN = false;//フルスクリーンかどうか
	inline constexpr int WINDOW_WIDTH = 1920;//ウィンドウの幅
	inline constexpr int WINDOW_HEIGHT = 1080;//ウィンドウの高さ
	inline constexpr float STICK_DEAD_ZONE = 0.3f;//スティックのデッドゾーン
	inline constexpr float TRIGGER_DEAD_ZONE = 0.3f;//トリガーのデッドゾーン
	inline constexpr int MAX_CONTROLLERS = 1;//コントローラーの数
	template<typename T>
	inline constexpr auto PI=static_cast<T>(3.1415926535897932384626433832795);//円周率

}