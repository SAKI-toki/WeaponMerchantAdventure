#pragma once
#include "../common/common.h"
#include "manager/sound_manager.h"

class Sound
{
	IXAudio2SourceVoice* source;
	SoundData sound_data;
	std::string name;
	bool is_loop; 
	XAUDIO2_BUFFER buffer{ 0 };
public:
	HRESULT init(const std::string&, const WCHAR*, const bool, const bool);
	void update();
	void play()
	{
		if (!source)return;
		source->Start();
	}
	void pause()
	{
		if (!source)return;
		source->Stop();
	}
	void stop()
	{
		if (!source)return;
		source->Stop();
		source->FlushSourceBuffers();
		source->SubmitSourceBuffer(&buffer);
	}
	bool is_play()
	{
		if (!source)return false;
		XAUDIO2_VOICE_STATE xa2scate;
		source->GetState(&xa2scate);
		return xa2scate.BuffersQueued != 0;
	}
	void set_volume(float volume)
	{
		if (!source)return;
		if (volume < 0)volume = 0;
		source->SetVolume(volume);
	}
	float get_volume()const
	{
		if (!source)return 0;
		float *p = new float;
		source->GetVolume(p);
		float vol = *p;
		if (p)delete(p);
		return vol;
	}
	void destroy()
	{
		if (!source)return;
		source->DestroyVoice();
	}
};