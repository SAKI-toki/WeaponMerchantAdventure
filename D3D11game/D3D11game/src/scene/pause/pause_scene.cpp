#include "pause_scene.h"
#include "../../input/gamepad/gamepad_input.h"
#include "../main/select/select_scene.h"

void PauseScene::Init()
{
	//黒のテクスチャの読み込み
	black.Init(std::string("black"), L"black.png", Vec2(1920, 1080));
	black.ColorChange(1.0f, 1.0f, 1.0f, 0.7f);
	next_scene[0].Init("return_game", L"return_game.png", Vec2(490, 137));
	next_scene[0].ColorChange(1.0f, 1.0f, 1.0f, 1.0f);
	next_scene[1].Init("return_select", L"return_select.png", Vec2(481, 133));
	next_scene[1].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
	move_sound.init(std::string("menu_move_sound"), L"menu_move.wav", false, false);
	accept_sound.init(std::string("menu_accept_sound"), L"menu_accept.wav", false, false);
}

std::shared_ptr<Scene> PauseScene::Update(std::shared_ptr<Scene>& scene_ptr)
{
	auto next_scene_ptr = scene_ptr;
	auto prev_select = current_select;
	//選択（上）
	if (current_select != 0 &&
		(GamepadInput::getinstance()->GetStick(0, false, false) > 0 ||
			GamepadInput::getinstance()->GetButton(0, BUTTON::DPAD_UP)))
	{
		if (!upflg)
		{
			--current_select;
			upflg = true;
			downflg = false;
		}
	}
	//選択（下）
	else if (current_select != 1 &&
		(GamepadInput::getinstance()->GetStick(0, false, false) < 0 ||
			GamepadInput::getinstance()->GetButton(0, BUTTON::DPAD_DOWN)))
	{
		if (!downflg)
		{
			++current_select;
			downflg = true;
			upflg = false;
		}
	}
	else if (GamepadInput::getinstance()->GetButtonDown(0, BUTTON::START))
	{
		accept_sound.stop();
		accept_sound.play();
		EndPause();
		BGM::getinstance()->SetVolume(1.0f);
	}
	//決定
	else if (GamepadInput::getinstance()->GetButtonDown(0, BUTTON::A))
	{
		accept_sound.stop();
		accept_sound.play();
		switch (current_select)
		{
		case 0:
			EndPause();
			BGM::getinstance()->SetVolume(1.0f);
			break;
		case 1:
			next_scene_ptr = std::make_shared<SelectScene>();
			break;
		}
	}
	else
	{
		upflg = false;
		downflg = false;
	}
	//色の変更
	if (prev_select != current_select)
	{
		move_sound.stop();
		move_sound.play();
		next_scene[prev_select].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
		next_scene[current_select].ColorChange(1.0f, 1.0f, 1.0f, 1.0f);
	}

	return next_scene_ptr;
}

void PauseScene::Render()
{
	if (!is_pause)return;
	black.Render(Transform({ 0,0,-4 },
		saki::vector3_zero<float>, saki::vector3_one<float>), false);
	//選択肢の描画
	for (int i = 0; i < 2; ++i)
	{
		next_scene[i].Render(Transform({ 0,(+200.0f - 400 * i),-3 },
			saki::vector3_zero<float>,
			Vec3(((current_select == i) ? 1.2f : 0.8f), ((current_select == i) ? 1.2f : 0.8f), 1)),
			false);
	}
}

void PauseScene::Destroy()
{

}