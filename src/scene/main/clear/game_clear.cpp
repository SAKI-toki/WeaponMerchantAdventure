/**
* @file game_clear.cpp
* @brief �Q�[���N���A�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/29
*/
#include "game_clear.h"

/**
* @brief �Q�[���N���A�V�[���̏�����
*/
void GameClearScene::Init()
{
	my_scene = SCENE::CLEAR;
}

/**
* @brief �Q�[���N���A�V�[���̍X�V
* @return SCENE �V�[�����ς��Ȃ玟�̃V�[����enum class��Ԃ�
*/
SCENE GameClearScene::Update()
{
	auto current_scene = my_scene;

	return current_scene;
}

/**
* @brief �Q�[���N���A�V�[���̕`��
*/
void GameClearScene::Render()
{

}

/**
* @brief �Q�[���N���A�V�[���̔j��
*/
void GameClearScene::Destroy()
{

}