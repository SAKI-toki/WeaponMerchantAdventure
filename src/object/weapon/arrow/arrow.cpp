/**
* @file arrow.cpp
* @brief ����������N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/18
*/
#include "arrow.h"
#include "../../../input/gamepad/gamepad_input.h"

/**
* @brief �R���X�g���N�^
*/
Arrow::Arrow()
{
	sprite.Init(std::string("arrow"), L"arrow.png", true, 32, 64, 1, 0, 0, 1.0f);
}

/**
* @brief �U��
* @param pos �e�𔭎˂���ʒu
*/
void Arrow::Attack(bool, const VEC2& pos)
{
	bullet.push_front(Bullet());
	
	std::begin(bullet)->Init("bullet", L"sample5.png", 32, 32, VEC2(pos.x, pos.y - 0.5f));
	std::begin(bullet)->BulletInit(stick_angle);
}

/**
* @brief ����̍X�V
*/
void Arrow::WeaponUpdate(const VEC2&, bool)
{
	//�E�X�e�B�b�N�̊p�x
	float stick_x = GamepadInput::GetInstance()->GetStick(true, true);
	float stick_y = GamepadInput::GetInstance()->GetStick(true, false);
	if (stick_x == 0 && stick_y == 0) { arrow_rendering = false; }
	else
	{
		arrow_rendering = true;
		{
			float ratio_x, angle;
			{
				float abs_sum = std::abs(stick_x) + std::abs(stick_y);
				ratio_x = std::abs(stick_x) / abs_sum;
			}
			angle = PI<float> / 2 * ratio_x;
			if (stick_x == 0)
			{
				if (stick_y < 0)angle = PI<float>;
				else angle = 0;
			}
			else if (stick_y == 0)
			{
				if (stick_x < 0)angle = PI<float>*1.5f;
				else angle = PI<float>*0.5f;
			}
			else if (stick_x > 0 && stick_y < 0)
			{
				angle = PI<float> -angle;
			}
			else if (stick_x < 0)
			{
				if (stick_y < 0)
				{
					angle += PI<float>;
				}
				else
				{
					angle = PI<float> * 2 - angle;
				}
			}
			stick_angle = angle;
		}
	}
	//�e�̍X�V
	auto itr = std::begin(bullet);
	while (itr != std::end(bullet))
	{
		itr->Update();
		if (!itr->enabled)
		{
			itr = bullet.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

/**
* @brief ����̕`��
* @param t �`��ʒu
*/
void Arrow::WeaponRender(const Transform& t)
{
	/*if (arrow_rendering)
	{*/
	//���̕`��
		sprite.Render(Transform(t.pos, stick_angle, 1));
	/*}*/
	//�e�̕`��
	for (auto&& n : bullet)
	{
		n.Render();
	}
}

/**
* @brief ����̔j��
*/
void Arrow::WeaponDestroy()
{
	bullet.clear();
}