/**
* @file title_scene.cpp
* @brief �^�C�g���V�[���N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/11/19
*/
#include "title_scene.h"
#include "../../../common/common.h"
#include "../../../object/camera/camera.h"
#include "../../../input/gamepad/gamepad_input.h"
#include "../../../sound/bgm/bgm.h"
#include "../../../collider/manager/collider_manager.h"

#include "../select/select_scene.h"

/**
* @brief �^�C�g���V�[���̏�����
*/
void TitleScene::Init()
{
	ColliderManager::GetInstance()->SetTarget(nullptr);
	//�v���C���[
	{
		player = std::make_unique<Player>();
		player->Init(std::string("player"), L"WizardWalkRight.png", 86, 128, { 200,200 }, 0, 0.6f);
	}
	//�}�b�v
	{
		MakeMap(map, { 64.0f * 0,64.0f * 5 }, 40, 4, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
		MakeMap(map, { 64.0f * 0,64.0f * -10 }, 2, 15, std::string("field1"), L"map/map2.png", 32, 32, 0, 2);
	}
	//�e�N�X�`��
	{
		background.Init("title_background", L"background/title_background.jpg", 1280, 640);
		finger_arrow.Init("finger_arrow", L"finger_arrow.png", 300, 237);
	}
	//�t�H���g
	{
		font.push_back(Font());
		font.push_back(Font());
		font.push_back(Font());
		font.push_back(Font());
		font[0].Init(L"�^");
		font[1].Init(L"�C");
		font[2].Init(L"�g");
		font[3].Init(L"��");
		font[0].SetTransform(Transform(VEC2(100, 300), 0, 9));
		font[1].SetTransform(Transform(VEC2(600, 300), 0, 9));
		font[2].SetTransform(Transform(VEC2(1100, 300), 0, 9));
		font[3].SetTransform(Transform(VEC2(1600, 300), 0, 9));
	}
	Camera::GetInstance()->SetTarget(nullptr);
	Camera::GetInstance()->SetPos({ 0.0f, 0.0f });
	BGM::GetInstance()->ChangeBgm(std::string("title_bgm"), L"BGM/title.wav");
}

/**
* @brief �^�C�g���V�[���̍X�V
* @return std::shared_ptr<Scene> �V�[�����ς��Ȃ玟�̃V�[����std::shared_ptr<Scene>��Ԃ�
*/
std::shared_ptr<Scene> TitleScene::Update(std::shared_ptr<Scene>& scene)
{
	auto current_scene = scene;
	player->Update();
	//�}�b�v�̍X�V
	for (auto&& m : map)
	{
		m.Update();
	}
	if (player->transform.pos.x >= WINDOW_WIDTH + 100.0f)
	{
		current_scene = std::make_shared<SelectScene>();
	}
	if (++finger_time > 60)
	{
		finger_time = 0;
	}
	return current_scene;
}

/**
* @brief �^�C�g���V�[���̕`��
*/
void TitleScene::Render()
{
	background.Render(Transform({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f }, 0, 1.8f), false);
	finger_arrow.Render(Transform({ 1000 + finger_time * 1.5f,0 }));
	for (auto&& f : font)
	{
		f.Render();
	}
	for (auto&& m : map)
	{
		m.Render();
	}
	player->Render();
	player->UiRender();
}

/**
* @brief �^�C�g���V�[���̔j��
*/
void TitleScene::Destroy()
{
	for (auto&& m : map)
	{
		m.Destroy();
	}
	player->Destroy();
}