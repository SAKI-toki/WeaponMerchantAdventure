#include "sound.h"

HRESULT Sound::init(const std::string& key, const WCHAR* path, const bool _is_loop, const bool is_awake)
{
	name = key;
	if (FAILED(SoundManager::getinstance()->load_sound(key, path)))
	{
		return E_FAIL;
	}
	sound_data = SoundManager::getinstance()->get_sound(key);
	buffer.pAudioData = sound_data.buffer;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = sound_data.wav_size;
	if (FAILED(SoundManager::getinstance()->get_ixaudio()->CreateSourceVoice(&source, sound_data.pwfex)))
	{
		Comment(L"サウンドの作成に失敗", L"sound.cpp");
		return E_FAIL;
	}
	if (FAILED(source->SubmitSourceBuffer(&buffer)))
	{
		Comment(L"ソースのSubmitに失敗", L"sound.cpp");
		return E_FAIL;
	}
	is_loop = _is_loop;
	if (is_awake)play();
	return S_OK;
}

void Sound::update()
{
	if (is_loop&&!is_play())
	{
		stop();
		play();
	}
}