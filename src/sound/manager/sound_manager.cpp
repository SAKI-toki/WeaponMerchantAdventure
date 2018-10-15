/**
* @file sound_manager.cpp
* @brief �T�E���h�}�l�[�W���[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/04
*/
#include "sound_manager.h"
#include <Dbt.h>
/**
* @brief �T�E���h�}�l�[�W���[�N���X�̏�����
* @param hWnd �E�B���h�E�n���h��
*/
void SoundManager::Init(HWND hWnd)
{
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif
	m_pAudioEngine = std::make_unique<DirectX::AudioEngine>(eflags);

	retry_audio = false;

	hNewAudio = nullptr;

	DEV_BROADCAST_DEVICEINTERFACE filter = {};
	filter.dbcc_size = sizeof(filter);
	filter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	filter.dbcc_classguid = KSCATEGORY_AUDIO;

	hNewAudio = RegisterDeviceNotification(hWnd, &filter, DEVICE_NOTIFY_WINDOW_HANDLE);
}

/**
* @brief �T�E���h�}�l�[�W���[�̍X�V
*/
void SoundManager::Update()
{
	if (retry_audio)
	{
		retry_audio = false;
		if (m_pAudioEngine->Reset())
		{

		}
	}
	else if (!m_pAudioEngine->Update())
	{
		if (m_pAudioEngine->IsCriticalError())
		{
			retry_audio = true;
		}
	}
}

/**
* @brief �T�E���h�}�l�[�W���[�̔j��
*/
void SoundManager::Destroy()
{
	Suspend();
	if (hNewAudio)UnregisterDeviceNotification(hNewAudio);
}

/**
* @brief �T�E���h��Ԃ�
* @param name map�ŊǗ����邽�߂̃L�[
* @param path wav�t�@�C���̃p�X
* @details �����t�@�C����2�x�ǂݍ��܂Ȃ��悤�ɂ���
*/
std::unique_ptr<DirectX::SoundEffect>& SoundManager::GetSound(std::string name, WCHAR* path)
{
	auto itr = soundList.find(name);
	if (itr == end(soundList))
	{
		WCHAR _path[256];
		wcscpy_s(_path, sound_path);
		wcscat_s(_path, path);
		soundList.insert(std::make_pair(name, std::make_unique<DirectX::SoundEffect>(SoundManager::GetInstance()->GetEngine(), _path)));
	}
	return soundList.at(name);

}
