/**
* @file sound.cpp
* @brief �T�E���h�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/10/04
*/
#include "sound.h"
#include "manager/sound_manager.h"

/**
* @brief �T�E���h�̏�����
* @param path �T�E���h�̃p�X
* @param loop ���[�v���邩�ǂ���
* @param awake �����������u�Ԃ���Đ����邩�ǂ���
*/
void Sound::Init(WCHAR* path, bool loop, bool awake)
{
	instance_sound = SoundManager::GetInstance()->GetSound(path)->CreateInstance();
	is_loop = loop;
	if (awake)Start();
}

/**
* @brief �f�X�g���N�^
*/
Sound::~Sound()
{
	instance_sound.reset();
}