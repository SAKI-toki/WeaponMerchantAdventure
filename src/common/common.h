/**
* @file common.h
* @brief �萔��`��w�b�_�̃C���N���[�h
* @author �ΎR�@�I
* @date 2018/10/29
*/
#pragma once
#include <Windows.h>
#include <d3d11.h>//���d3d11.h��d3d12.h���C���N���[�h���Ȃ���Simplemath.h���G���[�o��
#include <SimpleMath.h>
using VEC2 = DirectX::SimpleMath::Vector2;

namespace
{
	//�萔��`
	/*
	inline�ϐ����g�p���Ă��邽��C++17�ȍ~�̂ݗL��
	�ÓI�Ȓ萔��(static constexpr)�̏ꍇ�͎�����inline�������A�V�����K�i�̂��߁A�ꉞ�����I��inline�錾����
	*/
	inline constexpr bool FULL_SCREEN =
#ifdef _DEBUG
		false
#else
		true
#endif
		;
	//�t���X�N���[�����ǂ���
	inline constexpr int WINDOW_WIDTH = 1920;//�E�B���h�E�̕�
	inline constexpr int WINDOW_HEIGHT = 1080;//�E�B���h�E�̍���
	inline constexpr float L_STICK_DEAD_ZONE = 0.3f;//���X�e�B�b�N�̃f�b�h�]�[��
	inline constexpr float R_STICK_DEAD_ZONE = 0.05f;//�E�X�e�B�b�N�̃f�b�h�]�[��
	inline constexpr float TRIGGER_DEAD_ZONE = 0.3f;//�g���K�[�̃f�b�h�]�[��
	inline constexpr int MAX_CONTROLLERS = 1;//�R���g���[���[�̐�
	inline constexpr float DESTROY_Y = 600.0f;//����ȏ�I�u�W�F�N�g�����ɍs������f�X�g���C����
	inline constexpr float FADE_SPEED = 0.01f;//�t�F�[�h�C���A�A�E�g���鑬��
	//�~�����̕ϐ��e���v���[�g
	template<typename T>
	inline constexpr auto PI = static_cast<T>(3.1415926535897932384626433832795);
	inline constexpr WCHAR* texture_path = L"resources/texture/";	//�e�N�X�`���̃p�X
	inline constexpr WCHAR* sound_path = L"resources/sound/";		//�T�E���h�̃p�X
	//���b�Z�[�W�{�b�N�X���g���₷������
	template<typename T1, typename T2>
	void Comment(const T1& t1, const T2& t2 = L"")
	{
		MessageBox(NULL, t1, t2, MB_OK);
	}
	void Comment()
	{
		MessageBox(NULL, L"", L"", MB_OK);
	}
}