/**
* @file game_over.cpp
* @brief �Q�[���I�[�o�[�V�[���̒�`
* @author �ΎR�@�I
* @date 2018/11/26
*/
#include "game_over.h"
#include "../../../../input/gamepad/gamepad_input.h"
#include "../../../manager/scene_manager.h"
#include "../../select/select_scene.h"
#include "../../title/title_scene.h"
#include "../../../../sound/bgm/bgm.h"
#include "../../../../common/saki/random/random.h"

/**
* @brief �Q�[���I�[�o�[�V�[���̏�����
*/
void GameOver::Init()
{
	//���̃e�N�X�`���̓ǂݍ���
	black.Init(std::string("black"), L"black.png", 1920, 1080, 1.0f, 1.0f, 1.0f, 0.0f);
	game_over.Init("game_over", L"game_over.png", 238, 80);
	game_over.ColorChange(1.0f, 0.0f, 0.0f, 1.0f);
	blood.Init("blood", L"blood.png", 125, 203);
	next_scene[0].Init("one_more", L"one_more.png", 481, 133);
	next_scene[0].ColorChange(brightness, brightness, brightness, 1.0f);
	next_scene[1].Init("return_select", L"return_select.png", 481, 133);
	next_scene[1].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
	next_scene[2].Init("return_title", L"return_title.png", 481, 133);
	next_scene[2].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
}

/**
* @brief �Q�[���I�[�o�[�V�[���̍X�V
* @param scene_ptr ���݂̃V�[�������i�[���A�V�[���J�ڎ��ɂ����p����
* @param continue_next �Q�[���V�[�����ǂ̓�Փx���킩��悤�ɂ���
*/
void GameOver::Update(std::shared_ptr<Scene>& scene_ptr, std::shared_ptr<Scene>&& continue_next)
{
	//����������A�j���[�V����
	if (++current_blood_time > blood_time)
	{
		current_blood_time = 0;
		blood_time = saki::random(10, 30);
		blood_pos.push_back(blood_status());
		(std::end(blood_pos) - 1)->pos = { saki::random<float>(0.0f,WINDOW_WIDTH),-100 };
		(std::end(blood_pos) - 1)->scale = saki::random(0.1f, 0.5f);
	}
	//�t�F�C�h�C��
	if (alpha < alpha_limit)
	{
		//�ŏ�����BGM��ς��鏈�����s��
		if (std::exchange(first, false))
		{
			BGM::GetInstance()->ChangeBgm("over", L"BGM/over.wav");
			rendering_flg = true;
		}
		alpha += 0.01f;
	}
	//�t�F�C�h�C���I��
	else
	{
		if (time >= delay)
		{
			auto prev_select = current_select;
			//���邳�ύX
			{
				if (bright_down)
				{
					brightness -= 0.003f;
					if (brightness <= brightness_downlimit)
						bright_down = !bright_down;
				}
				else
				{
					brightness += 0.003f;
					if (brightness >= brightness_uplimit)
						bright_down = !bright_down;
				}
			}
			//�I���i��j
			if (current_select != 0 &&
				(GamepadInput::GetInstance()->GetStick(false, false) > 0 ||
					GamepadInput::GetInstance()->GetButton(BUTTON::DPAD_UP)))
			{
				if (!upflg)
				{
					--current_select;
					upflg = true;
					downflg = false;
				}
			}
			//�I���i���j
			else if (current_select != 2 &&
				(GamepadInput::GetInstance()->GetStick(false, false) < 0 ||
					GamepadInput::GetInstance()->GetButton(BUTTON::DPAD_DOWN)))
			{
				if (!downflg)
				{
					++current_select;
					downflg = true;
					upflg = false;
				}
			}
			//����
			else if (GamepadInput::GetInstance()->GetButton(BUTTON::A))
			{
				switch (current_select)
				{
				case 0:
					SceneManager::GetInstance()->ContinueGame(continue_next);
					return;
				case 1:
					scene_ptr = std::make_shared<SelectScene>();
					return;
				case 2:
					scene_ptr = std::make_shared<TitleScene>();
					return;
				}
			}
			else
			{
				upflg = false;
				downflg = false;
			}
			//�F�̕ύX
			if (prev_select != current_select)
			{
				next_scene[prev_select].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
			}
			next_scene[current_select].ColorChange(brightness, brightness, brightness, 1.0f);
		}
		else
		{
			++time;
		}
	}
}

/**
* @brief �Q�[���I�[�o�[�V�[���̕`��
*/
void GameOver::Render()
{
	if (!rendering_flg)return;
	//�F���Z�b�g
	SetColor();
	black.Render(Transform({ 0,0 }, 0, 1), false, false);
	game_over.Render(Transform({ WINDOW_WIDTH / 2.0f,300.0f },0,3.0f), false);
	//���̕`��
	auto itr = std::begin(blood_pos);
	while (itr != std::end(blood_pos))
	{
		blood.Render(Transform(itr->pos, 0.0f, itr->scale), false);
		itr->pos.y += 10;
		if (itr->pos.y > WINDOW_HEIGHT + 300)
		{
			itr = blood_pos.erase(itr);
		}
		else
		{
			++itr;
		}
	}
	//�I�����̕`��
	for (int i = 0; i < 3; ++i)
	{
		next_scene[i].Render(Transform({ WINDOW_WIDTH / 2.0f,(500.0f + 200.0f * i) + (delay - time) * 10.0f }, 0, ((current_select == i) ? 1.2f : 0.8f)), false);
	}
}