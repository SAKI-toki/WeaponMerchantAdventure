/**
* @file gamepad_input.h
* @brief �Q�[���p�b�h�̃C���v�b�g�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/04
*/
#pragma once
#include "../../common/common.h"
#include "../../common/singleton.h"
#include <Xinput.h>

/**
* @brief �{�^����enum class
* @details �f�t�H���g�̒����}�N�����g�킸�A�������ŊǗ�����
*/
enum class BUTTON {
	A, B, X, Y, START, BACK,
	DPAD_UP, DPAD_DOWN, DPAD_RIGHT, DPAD_LEFT,
	STICK_R, STICK_L, R1, L1, BUTTON_END
};

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

	//����1�ƈ���2�̘_���ς�����2�Ɗ��S�Ɉ�v���Ă���Ƃ��̂�true
	template<typename U1, typename U2>
	bool perfect_and(const U1 u1, const U2 u2)const
	{
		return (u1&u2) == u2;
	}

public:
	GamepadInput();

	void Update();


	///--�Q�b�^--
	/**
	* @brief �{�^�������������ǂ���
	* @param k ���肷��{�^��
	*/
	bool GetButtonDown(BUTTON b)const { return controller.bConnected&&controller.bConnected&&button_down[static_cast<int>(b)]; };
	/**
	* @brief �{�^���������Ă��邩�ǂ���
	* @param k ���肷��{�^��
	*/
	bool GetButton(BUTTON b)const { return controller.bConnected&&controller.bConnected&&button[static_cast<int>(b)]; };
	/**
	* @brief �{�^���𗣂������ǂ���
	* @param k ���肷��{�^��
	*/
	bool GetButtonUp(BUTTON b)const { return controller.bConnected&&controller.bConnected&&button_up[static_cast<int>(b)]; };

	/**
	* @brief �g���K�[�̏�Ԃ�Ԃ�
	* @param right ���肷��̂��E���ǂ���
	*/
	float GetTrigger(const bool right)const
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

	/**
	* @brief �X�e�B�b�N�̏�Ԃ�Ԃ�
	* @param right ���肷��̂��E���ǂ���
	* @param right ���肷��̂�x���ǂ���
	*/
	float GetStick(const bool right, const bool x)const
	{
		//�Ȃ����Ă��Ȃ�������0��Ԃ�
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
