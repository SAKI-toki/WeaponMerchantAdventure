/**
* @file arrow.cpp
* @brief ����������N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/18
*/
#include "arrow.h"
#include "../../../input/gamepad/gamepad_input.h"
#include "../../../common/saki/degree_radian/degree_radian_conversion.h"

/**
* @brief �R���X�g���N�^
*/
Arrow::Arrow()
{
	sprite.Init(std::string("arrow"), L"arrow.png",  32, 64, 1, 0, 0, 1.0f);
}

/**
* @brief ����p�̏�����
*/
void Arrow::WeaponStart()
{
	current_delay = delay;
}

/**
* @brief �U��
* @param pos �e�𔭎˂���ʒu
*/
void Arrow::Attack(bool, const VEC2& pos)
{
	if (current_delay < delay) { return; }
	current_delay = 0;
	bullet.push_front(Bullet());

	std::begin(bullet)->Init("bullet", L"sample5.png", 32, 32, VEC2(pos.x, pos.y - 0.5f));
	std::begin(bullet)->BulletInit(stick_angle, std::bind(&Arrow::CollisionBullet, this));
	sound.push_back(Sound());
	sound[sound.size() - 1].Init(std::string("bullet"), L"bullet.wav", false, true);
}

/**
* @brief ����̍X�V
*/
void Arrow::WeaponUpdate(const VEC2&, bool)
{
	if (current_delay < delay) { ++current_delay; }
	//�E�X�e�B�b�N�̊p�x
	float stick_x = GamepadInput::GetInstance()->GetStick(true, true);
	float stick_y = GamepadInput::GetInstance()->GetStick(true, false);
	//�E�X�e�B�b�N���|��Ă���Ƃ�
	if (stick_x != 0.0f || stick_y != 0.0f)
	{
		//��������Ă���Ƃ���0�x�ƂȂ�悤�Ɍv�Z����
		stick_angle = std::atan2f(-stick_y, stick_x) + saki::to_radian<float>(90.0f);
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
	//���̍X�V
	auto sound_itr = std::begin(sound);
	while (sound_itr != std::end(sound))
	{
		//�Đ��I�����Ă�����C�e���[�^�[���폜
		if (!sound_itr->Is_Play())
		{
			sound_itr = sound.erase(sound_itr);
		}
		else
		{
			++sound_itr;
		}
	}
}

/**
* @brief ����̕`��
* @param t �`��ʒu
*/
void Arrow::WeaponRender(const Transform& t)
{
	if (!weapon_enabled)return;
	if (current_delay >= delay)
	{	
		//���̕`��
		sprite.Render(Transform(t.pos, stick_angle, 1));
	}
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

/**
* @brief �e�����������Ƃ��Ɏ��s����֐�
*/
void Arrow::CollisionBullet()
{
	sound.push_back(Sound());
	sound[sound.size() - 1].Init(std::string("bullet_collision"), L"sample2.wav", false, true);
}