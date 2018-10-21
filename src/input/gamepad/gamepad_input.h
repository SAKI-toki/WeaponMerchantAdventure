/**
* @file gamepad_input.h
* @brief ゲームパッドのインプットクラスの宣言
* @author 石山　悠
* @date 2018/10/04
*/
#pragma once
#include "../../common/common.h"
#include "../../common/singleton.h"
#include <Xinput.h>

/**
* @brief ボタンのenum class
* @details デフォルトの長いマクロを使わず、こっちで管理する
*/
enum class BUTTON {
	A, B, X, Y, START, BACK,
	DPAD_UP, DPAD_DOWN, DPAD_RIGHT, DPAD_LEFT,
	STICK_R, STICK_L, R1, L1, BUTTON_END
};

/**
* @brief ゲームパッドのインプットクラス
*/
class GamepadInput :public Singleton<GamepadInput>
{
	//コントローラーは一つしか使わないから構造体も一つのみ用意
	struct CONTROLLER_STATE
	{
		XINPUT_STATE state;
		bool bConnected;
	} controller;

	//ボタンの状態
	bool button_down[14];
	bool button[14];
	bool button_up[14];

	//引数1と引数2の論理積が引数2と完全に一致しているときのみtrue
	template<typename U1, typename U2>
	bool perfect_and(const U1 u1, const U2 u2)const
	{
		return (u1&u2) == u2;
	}

public:
	GamepadInput();

	void Update();


	///--ゲッタ--
	/**
	* @brief ボタンを押したかどうか
	* @param k 判定するボタン
	*/
	bool GetButtonDown(BUTTON b)const { return controller.bConnected&&controller.bConnected&&button_down[static_cast<int>(b)]; };
	/**
	* @brief ボタンを押しているかどうか
	* @param k 判定するボタン
	*/
	bool GetButton(BUTTON b)const { return controller.bConnected&&controller.bConnected&&button[static_cast<int>(b)]; };
	/**
	* @brief ボタンを離したかどうか
	* @param k 判定するボタン
	*/
	bool GetButtonUp(BUTTON b)const { return controller.bConnected&&controller.bConnected&&button_up[static_cast<int>(b)]; };

	/**
	* @brief トリガーの状態を返す
	* @param right 判定するのが右かどうか
	*/
	float GetTrigger(const bool right)const
	{
		//つながっていなかったら0を返す
		if (!controller.bConnected) { return 0; }
		auto trigger = (right ? controller.state.Gamepad.bRightTrigger : controller.state.Gamepad.bLeftTrigger) / 255.0f;

		if (trigger > TRIGGER_DEAD_ZONE)
		{
			return trigger;
		}
		return 0;
	};

	/**
	* @brief スティックの状態を返す
	* @param right 判定するのが右かどうか
	* @param right 判定するのがxかどうか
	*/
	float GetStick(const bool right, const bool x)const
	{
		//つながっていなかったら0を返す
		if (!controller.bConnected) { return 0; }
		auto stick = (right ?
			(x ? controller.state.Gamepad.sThumbRX : controller.state.Gamepad.sThumbRY) :
			x ? controller.state.Gamepad.sThumbLX : controller.state.Gamepad.sThumbLY) / 32767.0f;

		if (std::abs(stick) > (right ? R_STICK_DEAD_ZONE : L_STICK_DEAD_ZONE))
		{
			return stick;
		}
		return 0;
	}
};
