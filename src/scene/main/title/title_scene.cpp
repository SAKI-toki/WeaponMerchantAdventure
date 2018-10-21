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
/**
* @brief �^�C�g���V�[���̏�����
*/
void TitleScene::Init()
{
	my_scene = SCENE::TITLE;
	font.Init(L"X��Y�𓯎������Ŏn�܂��");
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
	font.SetTransform(Transform(VEC2(100, 400), 0, 9));
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