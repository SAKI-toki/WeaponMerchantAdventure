/**
* @file arrow.cpp
* @brief ����������N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/18
*/
#include "arrow.h"
#include "../../../input/gamepad/gamepad_input.h"
#include <saki/math/degree_radian_conversion.h>

/**
* @brief ����p�̏�����
*/
void Arrow::WeaponStart()
{
	current_delay = delay;
}

/**
* @brief �U��
* @param right �E���ǂ���
* @param pos �e�𔭎˂���ʒu
*/
bool Arrow::Attack(bool right, const Vec3& pos)
{
	if (current_delay < delay) { return false; }
	current_delay = 0;	sound.push_back(Sound());
	sound[sound.size() - 1].init(std::string("bullet"), L"bullet.wav", false, true);
	bullet_flg = true;
	bullet_pos = pos;
	bullet_right = right;
	return true;
}

/**
* @brief ����̍X�V
*/
void Arrow::WeaponUpdate(const Vec3&, bool)
{
	if (current_delay < delay) { ++current_delay; }
	if (bullet_flg)
	{
		bullet_flg = false; 
		bullet.push_front(Bullet());
		std::begin(bullet)->Init("bullet", L"bullet.png", 32, 32, Vec3(bullet_pos.x, bullet_pos.y - 0.5f, -1));
		std::begin(bullet)->BulletInit((bullet_right) ? saki::to_radian<float>(90) : saki::to_radian<float>(-90), std::bind(&Arrow::CollisionBullet, this));
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
		if (!sound_itr->is_play())
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
void Arrow::WeaponRender(const Transform&)
{
	if (!weapon_enabled)return;
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
	sound[sound.size() - 1].init(std::string("bullet_collision"), L"sample2.wav", false, true);
}
