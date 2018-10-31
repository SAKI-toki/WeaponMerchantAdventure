/**
* @file bgm.h
* @brief BGMクラスの宣言
* @author 石山　悠
* @date 2018/10/30
*/
#pragma once
#include "../../common/common.h"
#include "../../common/singleton.h"
#include "../sound.h"

/**
* @brief BGMクラス
*/
class BGM :public Singleton<BGM>
{
	//BGM
	Sound bgm;
	//ボリューム
	float volume = 1.0f;
public:
	void Fade(const bool);
	void ChangeBgm(const std::string, WCHAR*);
};