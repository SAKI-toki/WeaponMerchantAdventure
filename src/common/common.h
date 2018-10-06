/**
* @file common.h
* @brief �萔��`��w�b�_�̃C���N���[�h
* @author �ΎR�@�I
* @date 2018/10/07
*/
#pragma once
#include <windows.h>
#include <string>
namespace
{
	//�萔��`
	inline constexpr bool FULL_SCREEN = false;//�t���X�N���[�����ǂ���
	inline constexpr int WINDOW_WIDTH = 1920;//�E�B���h�E�̕�
	inline constexpr int WINDOW_HEIGHT = 1080;//�E�B���h�E�̍���
	inline constexpr float STICK_DEAD_ZONE = 0.3f;//�X�e�B�b�N�̃f�b�h�]�[��
	inline constexpr float TRIGGER_DEAD_ZONE = 0.3f;//�g���K�[�̃f�b�h�]�[��
	inline constexpr int MAX_CONTROLLERS = 1;//�R���g���[���[�̐�
	template<typename T>
	inline constexpr auto PI=static_cast<T>(3.1415926535897932384626433832795);//�~����

}