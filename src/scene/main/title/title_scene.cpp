/**
* @file title_scene.cpp
* @brief �^�C�g���V�[���N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/10/02
*/
#include "title_scene.h"

/**
* @brief �^�C�g���V�[���̏�����
*/
void TitleScene::Init()
{
	my_scene = SCENE::TITLE;
}

/**
* @brief �^�C�g���V�[���̍X�V
* @return SCENE �V�[�����ς��Ȃ玟�̃V�[����enum class��Ԃ�
*/
SCENE TitleScene::Update()
{
	auto current_scene = my_scene;

	return current_scene;
}

/**
* @brief �^�C�g���V�[���̕`��
*/
void TitleScene::Render()
{

}

/**
* @brief �^�C�g���V�[���̔j��
*/
void TitleScene::Destroy()
{

}