/**
* @file bgm.h
* @brief BGM�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/30
*/
#pragma once
#include "../../common/common.h"
#include "../../common/singleton.h"
#include "../sound.h"

/**
* @brief BGM�N���X
*/
class BGM :public Singleton<BGM>
{
	//BGM
	Sound bgm;
	//�{�����[��
	float volume = 1.0f;
public:
	void Fade(const bool);
	void ChangeBgm(const std::string, WCHAR*);
};