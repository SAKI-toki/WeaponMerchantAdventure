#include "sound_manager.h"
extern void ExitGame();

HRESULT SoundManager::init()
{
	if (FAILED(CoInitializeEx(0, COINIT_MULTITHREADED)))
	{
		Comment(L"CoInitializeExに失敗", L"sound_manager.cpp");
		return E_FAIL;
	}
	if (FAILED(XAudio2Create(&ix_audio2, 0)))
	{
		Comment(L"xaudioの作成に失敗", L"sound_manager.cpp");
		return E_FAIL;
	}

	if (FAILED(ix_audio2->CreateMasteringVoice(&mastering_voice)))
	{
		Comment(L"MasteringVoiceの作成に失敗", L"sound_manager.cpp");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT SoundManager::load_sound(const std::string& key, const WCHAR* path)
{
	auto itr = sound_list.find(key);
	if (itr == std::end(sound_list))
	{
		WCHAR _path[256];
		wcscpy_s(_path, sound_path);
		wcscat_s(_path, path);
		SoundData sound_data;
		HMMIO hMmio = 0;
		DWORD dw_wav_size = 0;
		MMCKINFO ck_info, riffck_info;
		PCMWAVEFORMAT pcm_wave_form;
		hMmio = mmioOpen(_path, 0, MMIO_ALLOCBUF | MMIO_READ);
		if (hMmio == 0)
		{
			Comment(L"音声ファイルのパスが違います", L"sound_manager.cpp");
			return E_FAIL;
		}
		mmioDescend(hMmio, &riffck_info, 0, 0);
		ck_info.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hMmio, &ck_info, &riffck_info, MMIO_FINDCHUNK);
		mmioRead(hMmio, (HPSTR)(&pcm_wave_form), sizeof(pcmwaveformat_tag));
		sound_data.pwfex = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
		memcpy(sound_data.pwfex, &pcm_wave_form, sizeof(pcm_wave_form));
		sound_data.pwfex->cbSize = 0;
		mmioAscend(hMmio, &ck_info, 0);
		// WAVファイル内の音データの読み込み	
		ck_info.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hMmio, &ck_info, &riffck_info, MMIO_FINDCHUNK);//データチャンクにセット
		dw_wav_size = ck_info.cksize;
		//m_pWavBuffer[iIndex] = new BYTE[dwWavSize];
		sound_data.buffer = new BYTE[dw_wav_size];
		DWORD dwOffset = ck_info.dwDataOffset;
		mmioRead(hMmio, (HPSTR)sound_data.buffer, dw_wav_size);
		sound_data.wav_size = dw_wav_size;
		sound_list.insert(std::make_pair(key, sound_data));
	}
	return S_OK;
}

SoundData SoundManager::get_sound(const std::string& key)
{
	auto itr = sound_list.find(key);
	if (itr == std::end(sound_list))
	{
		ExitGame();
	}
	return itr->second;
}

void SoundManager::destroy()
{
	if (mastering_voice)
	{
		mastering_voice->DestroyVoice();
		mastering_voice = 0;
	}
	CoUninitialize();
}