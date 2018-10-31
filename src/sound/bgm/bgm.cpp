/**
* @file bgm.cpp
* @brief BGMクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/10/30
*/
#include "bgm.h"

/**
* @brief 主にシーン遷移時になめらかにBGMを変えるため
* @param fade_in フェードインかどうか
*/
void BGM::Fade(const bool fade_in)
{
	//フェードインかアウトによって加算するか減算するか決める
	volume += fade_in ? FADE_SPEED : -FADE_SPEED;
	//0より小さくなったら0に戻す
	if (volume < 0.0f)
	{
		volume = 0.0f;
	}
	//1より大きくなったら1に戻す
	else if (volume > 1.0f)
	{
		volume = 1.0f;
	}
	bgm.SetVolume(volume);
}

/**
* @brief BGMを変える
* @param name キー
* @param path パス
*/
void BGM::ChangeBgm(const std::string name, WCHAR* path)
{
	bgm.SetVolume(0.0f);
	bgm.Stop();
	bgm.Destroy();
	bgm.Init(name, path, true, true);
	bgm.Start();
	bgm.SetVolume(volume);
}