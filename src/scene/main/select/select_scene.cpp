/**
* @file select_scene.cpp
* @brief �Z���N�g�V�[���N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/19
*/
#include "select_scene.h"

/**
* @brief �Z���N�g�V�[���̏�����
*/
void SelectScene::Init()
{
	my_scene = SCENE::SELECT;
}

/**
* @brief �Z���N�g�V�[���̍X�V
* @return SCENE �V�[�����ς��Ȃ玟�̃V�[����enum class��Ԃ�
*/
SCENE SelectScene::Update()
{
	auto current_scene = my_scene;

	return current_scene;
}

/**
* @brief �Z���N�g�V�[���̕`��
*/
void SelectScene::Render()
{

}

/**
* @brief �Z���N�g�V�[���̔j��
*/
void SelectScene::Destroy()
{

}