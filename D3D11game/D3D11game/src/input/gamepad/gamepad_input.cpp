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
		for (size_t j = 0; j < CONTROLLER_NUM; ++j)
		{
			old_button[j][i] = false;
			current_button[j][i] = false;
		}
	}
}

/**
* @brief �Q�[���p�b�h�C���v�b�g�̍X�V
*/
void GamepadInput::Update()
{
	for (size_t n = 0; n < CONTROLLER_NUM; ++n)
	{
		auto dw_result = XInputGetState(static_cast<DWORD>(n), &controller[n].state);
		for (int i = 0; i < 14; ++i)
		{
			old_button[n][i] = current_button[n][i];
		}
		if (dw_result == ERROR_SUCCESS)
		{
			controller[n].bConnected = true;
			//�{�^���̍X�V
			{
				auto dw_buttons = controller[n].state.Gamepad.wButtons;
				bool button[] = { perfect_and(dw_buttons,XINPUT_GAMEPAD_A),
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
					current_button[n][i] = button[i];
				}
			}
		}
		//�R���g���[���[���ڑ�
		else
		{
			controller[n].bConnected = false;
			for (int i = 0; i < 14; ++i)
			{
				current_button[n][i] = false;
			}
		}
	}
	UpdateVibration();
}

/**
* @brief �R���g���[���[�̐U��
* @param right �E�̃��[�^�[�̗�
* @param left ���̃��[�^�[�̗�
*/
void GamepadInput::Vibration(size_t index, float right, float left)
{
	if (!index_check(index))return;
	//���ڑ�
	if (!controller[index].bConnected)return;
	//�͈͓��̐U���Ɏ��߂�
	{
		if (right < 0)right = 0;
		else if (right > 1.0f)right = 1.0f;
		if (left < 0)left = 0;
		else if (left > 1.0f)left = 1.0f;
	}
	right_power[index] = right;
	left_power[index] = left;
}

void GamepadInput::UpdateVibration()
{
	for (size_t n = 0; n < CONTROLLER_NUM; ++n)
	{
		if (right_power[n] == 0.0f&&left_power[n] == 0.0f)continue;
		//���ڑ�
		if (!controller[n].bConnected)
		{
			continue;
		}
		right_power[n] -= 0.03f;
		left_power[n] -= 0.03f;
		if (right_power[n] < 0.0f)right_power[n] = 0.0f;
		if (left_power[n] < 0.0f)left_power[n] = 0.0f;
		XINPUT_VIBRATION vibration;
		vibration.wRightMotorSpeed = static_cast<WORD>(UINT16_MAX * right_power[n]);
		vibration.wLeftMotorSpeed = static_cast<WORD>(UINT16_MAX * left_power[n]);
		XInputSetState(static_cast<DWORD>(n), &vibration);
	}
}