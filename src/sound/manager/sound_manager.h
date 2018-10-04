/**
* @file sound_manager.h
* @brief �T�E���h�}�l�[�W���[�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/04
*/
#pragma once
#include "../../common/common.h"
#include "../../common/singleton.h"
#include "Audio.h"

/**
* @brief �T�E���h���Ǘ�����N���X
*/
class SoundManager :public Singleton<SoundManager>
{
	//�K�v�Ȃ���
	HDEVNOTIFY hNewAudio;
	std::unique_ptr<DirectX::AudioEngine> m_pAudioEngine;
	bool retry_audio;

	//1�x�ǂݍ��񂾂��̂�2��ǂݍ��܂Ȃ�
	//�p�X�ŊǗ�
	std::unordered_map<WCHAR*, std::unique_ptr<DirectX::SoundEffect>> soundList;
public:
	std::unique_ptr<DirectX::SoundEffect>& GetSound(WCHAR*);

	void Init(HWND);
	void Update();
	void Destroy();

	//AudioEngine��Ԃ�
	auto GetEngine() { return m_pAudioEngine.get(); }

	//�K�v�Ȃ���
	void RetryAudio() { retry_audio = true; }
	void Suspend() { if (m_pAudioEngine)m_pAudioEngine->Suspend(); }
	void Resume() { if (m_pAudioEngine)m_pAudioEngine->Resume(); }
};