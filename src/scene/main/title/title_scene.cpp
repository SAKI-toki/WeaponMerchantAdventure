/**
* @file title_scene.cpp
* @brief �^�C�g���V�[���N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/10/02
*/
#include "title_scene.h"
#include "../../../common/common.h"
/**
* @brief �^�C�g���V�[���̏�����
*/
void TitleScene::Init()
{
	my_scene = SCENE::TITLE;
	player.Init(L"resources/texture/sample3.png", 100, 200, { 500,500 });
}

/**
* @brief �^�C�g���V�[���̍X�V
* @return SCENE �V�[�����ς��Ȃ玟�̃V�[����enum class��Ԃ�
*/
SCENE TitleScene::Update()
{
	auto current_scene = my_scene;
	player.Update();
	player.transform.rot += PI<float> * 2 / 100;
	return current_scene;
}

/**
* @brief �^�C�g���V�[���̕`��
*/
void TitleScene::Render()
{
	player.Render();
}

/**
* @brief �^�C�g���V�[���̔j��
*/
void TitleScene::Destroy()
{

}