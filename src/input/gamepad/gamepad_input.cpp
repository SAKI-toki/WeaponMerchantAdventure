/**
* @file gamepad_input.cpp
* @brief �Q�[���p�b�h�̃C���v�b�g�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/02
*/
#include "gamepad_input.h"

/**
* @brief �R���X�g���N�^�ŏ�����
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
* @brief �Q�[���p�b�h�C���v�b�g�̍X�V
*/
void GamepadInput::Update()
{
	auto dw_result = XInputGetState(0, &controller.state);
	if (dw_result == ERROR_SUCCESS)
	{
		controller.bConnected = true;
		//�{�^���̍X�V
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
				//�O�񉟂��Ă��Ȃ��č��񉟂�����down��on�ɂ���
				if (!button[i] && _button[i])
				{
					button_down[i] = true;
				}
				else
				{
					button_down[i] = false;
				}
				//�O�񉟂��Ă��č��񉟂��Ă��Ȃ�������up��off�ɂ���
				if (button[i] && !_button[i])
				{
					button_up[i] = true;
				}
				else
				{
					button_up[i] = false;
				}
				//��Ԃ����̂܂ܓn��
				button[i] = _button[i];
			}
		}
	}
	else
	{
		controller.bConnected = false;
	}
}