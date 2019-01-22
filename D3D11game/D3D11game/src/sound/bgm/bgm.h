/**
* @file bgm.h
* @brief BGM�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/30
*/
#pragma once
#include "../../common/common.h"
#include <saki/singleton/singleton.h>
#include "../sound.h"

/**
* @brief BGM�N���X
*/
class BGM :public saki::Singleton<BGM>
{
	//BGM
	Sound bgm;
	//�{�����[��
	float volume = 1.0f;
public:
	void Fade(const bool);
	void ChangeBgm(const std::string&, WCHAR*);
	void SetVolume(const float v)
	{
		volume = v;
		bgm.set_volume(volume);
	}
	void OneShotBGM(const std::string&, WCHAR*);
};