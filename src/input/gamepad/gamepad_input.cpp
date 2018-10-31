/**
* @file gamepad_input.cpp
* @brief ゲームパッドのインプットクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/02
*/
#include "gamepad_input.h"
#include <Windows.h>

/**
* @brief コンストラクタで初期化
*/
GamepadInput::GamepadInput()
{
	for (int i = 0; i < 14; ++i)
	{
		button[i] = false;
		button_up[i] = false;
		button_down[i] = false;
	}
}

/**
* @brief ゲームパッドインプットの更新
*/
void GamepadInput::Update()
{
	auto dw_result = XInputGetState(0, &controller.state);
	if (dw_result == ERROR_SUCCESS)
	{
		controller.bConnected = true;
		//ボタンの更新
		{
			auto dw_buttons = controller.state.Gamepad.wButtons;
			bool _button[] = { perfect_and(dw_buttons,XINPUT_GAMEPAD_A),
								perfect_and(dw_buttons,XINPUT_GAMEPAD_B),
								perfect_and(dw_buttons,XINPUT_GAMEPAD_X),
								perfect_and(dw_buttons,XINPUT_GAMEPAD_Y),
								perfect_and(dw_buttons,XINPUT_GAMEPAD_START),
								perfect_and(dw_buttons,XINPUT_GAMEPAD_BACK),
								perfect_and(dw_buttons,XINPUT_GAMEPAD_DPAD_UP) ,
								perfect_and(dw_buttons,XINPUT_GAMEPAD_DPAD_DOWN),
								perfect_and(dw_buttons,XINPUT_GAMEPAD_DPAD_RIGHT),
								perfect_and(dw_buttons,XINPUT_GAMEPAD_DPAD_LEFT),
								perfect_and(dw_buttons,XINPUT_GAMEPAD_RIGHT_THUMB),
								perfect_and(dw_buttons,XINPUT_GAMEPAD_LEFT_THUMB),
								perfect_and(dw_buttons,XINPUT_GAMEPAD_RIGHT_SHOULDER),
								perfect_and(dw_buttons,XINPUT_GAMEPAD_LEFT_SHOULDER) };

			for (int i = 0; i < 14; ++i)
			{
				//前回押していなくて今回押したらdownをonにする
				if (!button[i] && _button[i])
				{
					button_down[i] = true;
				}
				else
				{
					button_down[i] = false;
				}
				//前回押していて今回押していなかったらupをoffにする
				if (button[i] && !_button[i])
				{
					button_up[i] = true;
				}
				else
				{
					button_up[i] = false;
				}
				//状態をそのまま渡す
				button[i] = _button[i];
			}
		}
	}
	//コントローラー未接続
	else
	{
		controller.bConnected = false;
	}
}

/**
* @brief コントローラーの振動
* @param right 右のモーターの力
* @param left 左のモーターの力
*/
void GamepadInput::Vibration(float right, float left)
{
	//未接続
	if (!controller.bConnected)return;
	//範囲内の振動に収める
	{
		if (right < 0)right = 0;
		else if (right > 1.0f)right = 1.0f;
		if (left < 0)left = 0;
		else if (left > 1.0f)left = 1.0f;
	}
	XINPUT_VIBRATION vibration;
	vibration.wRightMotorSpeed = static_cast<WORD>(UINT8_MAX * right);
	vibration.wLeftMotorSpeed = static_cast<WORD>(UINT8_MAX * left);
	XInputSetState(0, &vibration);
}