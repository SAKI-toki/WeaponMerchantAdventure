/**
* @file common.h
* @brief �萔��`��w�b�_�̃C���N���[�h
* @author �ΎR�@�I
* @date 2018/10/07
*/
#pragma once
namespace
{
	//�萔��`
	/*
	inline�ϐ����g�p���Ă��邽��C++17�ȍ~�̂ݗL��
	*/
	inline constexpr bool FULL_SCREEN = false;//�t���X�N���[�����ǂ���
	inline constexpr int WINDOW_WIDTH = 1920;//�E�B���h�E�̕�
	inline constexpr int WINDOW_HEIGHT = 1080;//�E�B���h�E�̍���
	inline constexpr float STICK_DEAD_ZONE = 0.3f;//�X�e�B�b�N�̃f�b�h�]�[��
	inline constexpr float TRIGGER_DEAD_ZONE = 0.3f;//�g���K�[�̃f�b�h�]�[��
	inline constexpr int MAX_CONTROLLERS = 1;//�R���g���[���[�̐�
	//�~�����̕ϐ��e���v���[�g
	template<typename T>
	inline constexpr auto PI=static_cast<T>(3.1415926535897932384626433832795);
	inline constexpr WCHAR* texture_path = L"resources/texture/";	//�e�N�X�`���̃p�X
	inline constexpr WCHAR* sound_path = L"resources/sound/";		//�T�E���h�̃p�X
	//���b�Z�[�W�{�b�N�X���g���₷������
	template<typename T1,typename T2>
	void Comment(const T1& t1, const T2& t2)
	{
		MessageBox(NULL, t1, t2, MB_OK);
	}
}