#pragma once
#include <saki/singleton/singleton.h>
#include "../../common/common.h"
#include <xaudio2.h>
#include <string>
#include <unordered_map>
#pragma comment(lib,"winmm.lib")
struct SoundData
{
	DWORD wav_size;
	WAVEFORMATEX* pwfex;
	BYTE* buffer;
};
class SoundManager :public saki::Singleton<SoundManager>
{
	IXAudio2* ix_audio2;
	IXAudio2MasteringVoice* mastering_voice;
	std::unordered_map < std::string, SoundData> sound_list;
public:
	HRESULT init();
	HRESULT load_sound(const std::string&, const WCHAR*);
	SoundData get_sound(const std::string&);
	void destroy();

	IXAudio2*& get_ixaudio() { return (ix_audio2); }
};