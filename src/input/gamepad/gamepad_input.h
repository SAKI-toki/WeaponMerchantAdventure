/**
* @file gamepad_input.h
* @brief �Q�[���p�b�h�̃C���v�b�g�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/02
*/
#pragma once
#include "../../common/common.h"
#include "../../common/singleton.h"
#include <Xinput.h>

/**
* @brief �{�^����enum class
* @details �f�t�H���g�̒����}�N�����g�킸�A�������ŊǗ�����
*/
enum class BUTTON { A, B, X, Y, START, BACK,
DPAD_UP, DPAD_DOWN, DPAD_RIGHT, DPAD_LEFT,
STICK_R, STICK_L, R1, L1, BUTTON_END };

/**
* @brief �Q�[���p�b�h�̃C���v�b�g�N���X
*/
class GamepadInput :public Singleton<GamepadInput>
{
	//�R���g���[���[�͈�����g��Ȃ�����\���̂���̂ݗp��
	struct CONTROLLER_STATE
	{
		XINPUT_STATE state;
		bool bConnected;
	} controller;

	//�{�^���̏��
	bool button_down[14];
	bool button[14];
	bool button_up[14];


public:
	GamepadInput();

	void Update();


	///--�Q�b�^--//
	//�{�^���̏�Ԃ�Ԃ�
	bool GetButtonDown(BUTTON k)const { return controller.bConnected&&button_down[static_cast<int>(k)]; };
	bool GetButton(BUTTON k)const { return controller.bConnected&&button[static_cast<int>(k)]; };
	bool GetButtonUp(BUTTON k)const { return controller.bConnected&&button_up[static_cast<int>(k)]; };

	//�g���K�[�̏�Ԃ�Ԃ�
	float GetTrigger(bool right)const
	{
		//�Ȃ����Ă��Ȃ�������0��Ԃ�
		if (!controller.bConnected) { return 0; }
		auto trigger = (right ? controller.state.Gamepad.bRightTrigger : controller.state.Gamepad.bLeftTrigger) / 255.0f;
		
		if (trigger > TRIGGER_DEAD_ZONE)
		{
			return trigger;
		}
		return 0;
	};

	//�X�e�B�b�N�̏�Ԃ�Ԃ�
	float GetStick(bool right, bool x)const
	{
		//�Ȃ����Ă��Ȃ�������0��Ԃ�
		if (!controller.bConnected) { return 0; }
		auto stick = (right ?
			(x ? controller.state.Gamepad.sThumbRX : controller.state.Gamepad.sThumbRY) :
			x ? controller.state.Gamepad.sThumbLX : controller.state.Gamepad.sThumbLY) / 32767.0f;

		if (std::abs(stick) > STICK_DEAD_ZONE)
		{
			return stick;
		}
		return 0;
	}
};