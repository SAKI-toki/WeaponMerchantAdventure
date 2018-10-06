/**
* @file sound.h
* @brief �T�E���h�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/04
*/
#pragma once
#include <string>
#include <optional>
#include <Audio.h>

/**
* @brief�@�X�̃T�E���h�N���X
*/
class Sound
{
	std::unique_ptr<DirectX::SoundEffectInstance> instance_sound;
	//���[�v���邩�ǂ���
	bool is_loop;
public:
	void Init(WCHAR*, bool, bool);

	//�Đ�
	void Start() { instance_sound->Play(is_loop); }
	//��~
	void Stop() { instance_sound->Stop(); }
	//�ꎞ��~
	void Pause() { instance_sound->Pause(); }
	//�{�����[��
	void SetVolume(float vol) { instance_sound->SetVolume(vol); }
	//�s�b�`
	void SetPitch(float pit) { instance_sound->SetPitch(pit); }
	//�p��
	void SetPan(float pan) { instance_sound->SetPan(pan); }

	~Sound();

	std::unique_ptr<DirectX::SoundEffectInstance>& operator()()
	{
		return instance_sound;
	}
};