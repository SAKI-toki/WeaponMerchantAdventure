/**
* @file game_over.cpp
* @brief �Q�[���I�[�o�[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/29
*/
#include "game_over.h"

/**
* @brief �Q�[���I�[�o�[�V�[���̏�����
*/
void GameOverScene::Init()
{
	my_scene = SCENE::OVER;
}

/**
* @brief �Q�[���I�[�o�[�V�[���̍X�V
* @return SCENE �V�[�����ς��Ȃ玟�̃V�[����enum class��Ԃ�
*/
SCENE GameOverScene::Update()
{
	auto current_scene = my_scene;

	return current_scene;
}

/**
* @brief �Q�[���I�[�o�[�V�[���̕`��
*/
void GameOverScene::Render()
{

}

/**
* @brief �Q�[���I�[�o�[�V�[���̔j��
*/
void GameOverScene::Destroy()
{

}