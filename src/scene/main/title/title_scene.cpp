/**
* @file title_scene.cpp
* @brief �^�C�g���V�[���N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/10/16
*/
#include "title_scene.h"
#include "../../../common/common.h"
#include "../../../object/camera/camera.h"
#include "../../../input/gamepad/gamepad_input.h"
#include "../../../sound/bgm/bgm.h"
/**
* @brief �^�C�g���V�[���̏�����
*/
void TitleScene::Init()
{
	my_scene = SCENE::TITLE;
	font.Init(L"X��Y�𓯎������Ŏn�܂��");
	font.SetTransform(Transform(VEC2(100, 400), 0, 9));
	BGM::GetInstance()->ChangeBgm(std::string("title_bgm"), L"BGM/title.wav");
}

/**
* @brief �^�C�g���V�[���̍X�V
* @return SCENE �V�[�����ς��Ȃ玟�̃V�[����enum class��Ԃ�
*/
SCENE TitleScene::Update()
{
	auto current_scene = my_scene;
	if (GamepadInput::GetInstance()->GetButton(BUTTON::X) &&
		GamepadInput::GetInstance()->GetButton(BUTTON::Y))
	{
		current_scene = SCENE::GAME;
	}
	return current_scene;
}

/**
* @brief �^�C�g���V�[���̕`��
*/
void TitleScene::Render()
{
	font.Render();
}

/**
* @brief �^�C�g���V�[���̔j��
*/
void TitleScene::Destroy()
{

}