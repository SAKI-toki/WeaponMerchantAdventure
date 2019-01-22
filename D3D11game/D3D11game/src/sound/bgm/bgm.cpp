/**
* @file bgm.cpp
* @brief BGM�N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/10/30
*/
#include "bgm.h"

/**
* @brief ��ɃV�[���J�ڎ��ɂȂ߂炩��BGM��ς��邽��
* @param fade_in �t�F�[�h�C�����ǂ���
*/
void BGM::Fade(const bool fade_in)
{
	//�t�F�[�h�C�����A�E�g�ɂ���ĉ��Z���邩���Z���邩���߂�
	volume += fade_in ? FADE_SPEED : -FADE_SPEED;
	//0��菬�����Ȃ�����0�ɖ߂�
	if (volume < 0.0f)
	{
		volume = 0.0f;
	}
	//1���傫���Ȃ�����1�ɖ߂�
	else if (volume > 1.0f)
	{
		volume = 1.0f;
	}
	bgm.set_volume(volume);
}

/**
* @brief BGM��ς���
* @param name �L�[
* @param path �p�X
*/
void BGM::ChangeBgm(const std::string& name, WCHAR* path)
{
	bgm.set_volume(0.0f);
	bgm.stop();
	bgm.destroy();
	bgm.init(name, path, true, true);
	bgm.play();
	bgm.set_volume(volume);
}
/**
* @brief BGM��ς���(���[�v�Ȃ�)
* @param name �L�[
* @param path �p�X
*/
void BGM::OneShotBGM(const std::string& name, WCHAR* path)
{
	bgm.set_volume(0.0f);
	bgm.stop();
	bgm.destroy();
	bgm.init(name, path, false, true);
	bgm.play();
	bgm.set_volume(volume);
}