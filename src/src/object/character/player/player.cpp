/**
* @file player.cpp
* @brief �v���C���[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/11/19
*/
#include "player.h"
#include "../../../input/gamepad/gamepad_input.h"

/**
* @brief ������
*/
void Player::InitProcess()
{
	//�eUI�̏�����
	for (int i = 0; i < 10; ++i)
	{
		WCHAR  path[256];
		std::string name("num_");
		name += '0' + static_cast<char>(i);
		swprintf_s(path, L"number/num%d.png", i);
		bullet_ui[i].Init(name, path, Vec2(84, 80));
	}
	//�X���b�V���̏�����
	slash_ui.Init(("slash"), L"number/slash.png", Vec2(64, 79));
	slash_ui.ColorChange(0.0f, 0.0f, 0.0f, 1.0f);
	//����UI�̏�����
	which_weapon_ui[0].Init("weapon_ui_sword", L"sword_ui.png", Vec2(592, 592));
	which_weapon_ui[0].ColorChange(0.5f, 0.5f, 0.5f, 1);
	which_weapon_ui[1].Init("weapon_ui_magic", L"magic_ui.png", Vec2(592, 592));
	gravity.Init(max_speed);
	gravity.ResetGravity();
	transform.move(gravity.AddGravity());
	jump_sound.init(std::string("jump_sound"), L"jump.wav", false, false);
	get_item.init("get_item", L"get_item.wav", false, false);
	not_fire.init(std::string("non_fire_sound"), L"non_bullet.wav", false, false);
	destroy_sound.init(std::string("player_destroy_sound"), L"player_destroy.wav", false, false);
	status.Init(100, 10, 1);
	collider.SetStatus(transform.get_pos(), size.x, size.y, transform.get_scale()*collider_scale);
	weapon[weapon_num]->WeaponStart();
	anim.Init(size, 6, 8, 0);
	anim.ChangeAnimation((dire == DIRE::RIGHT) ? 7 : 3, 30);
	sprite.slice_num = { 6,8 };
}

/**
* @brief �v���C���[�̍X�V
*/
void Player::UpdateProcess()
{
	if (transform.get_pos().y < DESTROY_Y)
	{
		Destroy();
		return;
	}
	anim.Update();
	if (!destroy_flg)
	{
		//�W�����v
		if (GamepadInput::getinstance()->GetButtonDown(0, BUTTON::A))
		{
			//�W�����v�������ɉ���炷
			if (gravity.SetUpPower(jump))
			{
				jump_sound.stop();
				jump_sound.play();
			}
		}
		//�ړ�
		{
			float x = GamepadInput::getinstance()->GetStick(0, false, true);
			//�E�Ɉړ�
			if (x > 0)
			{
				if (std::abs(gravity.GetSidePower()) > max_speed / x)
				{
					gravity.ReturnZero(speed);
				}
				else
				{
					gravity.SetMaxSpeed(max_speed*x);
					gravity.SetSidePower(speed*x);
				}
				dire = DIRE::RIGHT;
				anim.ChangeAnimation(7, 10);
				anim.Changetime(static_cast<int>(5 / (std::abs(gravity.GetSidePower()) / max_speed)));
			}
			//���Ɉړ�
			else if (x < 0)
			{
				if (std::abs(gravity.GetSidePower()) > max_speed / -x)
				{
					gravity.ReturnZero(speed);
				}
				else
				{
					gravity.SetMaxSpeed(max_speed*-x);
					gravity.SetSidePower(-speed * -x);
				}
				dire = DIRE::LEFT;
				anim.ChangeAnimation(3, 10);
				anim.Changetime(static_cast<int>(5 / (std::abs(gravity.GetSidePower()) / max_speed)));
			}
			//�~�܂��Ă���
			else
			{
				//���S�Ɏ~�܂���
				if (gravity.ReturnZero(speed*1.5f))
				{
					anim.Changetime(30);
				}
			}
		}
		//����̐؂�ւ�
		{
			auto prev = weapon_num;
			if (weapon_num != 1 && GamepadInput::getinstance()->GetButtonDown(0, BUTTON::L1))
			{
				weapon_num = 1;
			}
			if (weapon_num != 0 && GamepadInput::getinstance()->GetButtonDown(0, BUTTON::R1))
			{
				weapon_num = 0;
			}
			if (weapon_num != prev)
			{
				which_weapon_ui[prev].ColorChange(0.5f, 0.5f, 0.5f, 1.0f);
				weapon[prev]->WeaponDestroy();
				weapon[weapon_num]->WeaponStart();
				which_weapon_ui[weapon_num].ColorChange(1.0f, 1.0f, 1.0f, 1.0f);
			}
			weapon[weapon_num]->WeaponUpdate(transform.get_pos(), dire == DIRE::RIGHT ? true : false);
		}
		//�U��
		if (GamepadInput::getinstance()->GetButtonDown(0, BUTTON::X))
		{
			Attack();
		}
	}
	//�d��
	transform.move(gravity.AddGravity());
	if (!destroy_flg)collider.SetStatus(transform.get_pos(),
		size.x, size.y, transform.get_scale()*collider_scale);
}

/**
* @brief �v���C���[�̕`��
* @param camera_affected �J�����̈ʒu�ɂ���ĕ`�悷��ʒu��ς��邩�ǂ���
*/
void Player::RenderProcess(bool camera_affected)
{
	//sprite.SetRect(anim.GetAnimation());
	sprite.current_slice = anim.GetAnimation();
	sprite.Render(transform, camera_affected);
	weapon[weapon_num]->WeaponRender(transform);
}

/**
* @brief �v���C���[�̔j��
*/
void Player::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
	weapon[weapon_num]->WeaponDestroy();
}

/**
* @brief �������Ă�Ƃ��Ɏ��s����֐�
*/
void Player::Collision(ObjectBase* obj, Vec2)
{
	if (obj == nullptr)return;
	if (translation_flg&&collider.collision_is_static_x&&obj->object_tag == OBJECT_TAG::MAP)
	{
		gravity.SetUpPower(10);
	}
	else if (obj->object_tag == OBJECT_TAG::ENEMY ||
		obj->object_tag == OBJECT_TAG::BOSS ||
		obj->object_tag == OBJECT_TAG::BOSS_BULLET)
	{
		destroy_sound.play();
		collider.Destroy();
		destroy_flg = true;
		gravity.ResetGravity();
		gravity.ResetSideGravity();
		gravity.SetUpPower(5);
		weapon[weapon_num]->WeaponDestroy();
		EnabledWeapon();
		auto rot = transform.get_rot();
		rot.x = saki::PI<float>;
		transform.set_rot(rot);

	}
	else if (obj->object_tag == OBJECT_TAG::BOSS_ZONE)
	{
		boss_scene = true;
		gravity.ResetGravity();
		gravity.ResetSideGravity();
	}
	else if (obj->object_tag == OBJECT_TAG::BULLET_ITEM)
	{
		if (remaining_bullet < max_bullet)++remaining_bullet;
		//�Q�b�g��
		get_item.stop();
		get_item.play();
	}
}


/**
* @brief �U��
*/
void Player::Attack()
{
	if (weapon_num == 1 && remaining_bullet <= 0)
	{
		//�s����
		not_fire.stop();
		not_fire.play();
		return;
	}
	if (weapon[weapon_num]->Attack((dire == DIRE::RIGHT ? true : false), transform.get_pos()))
	{
		if (weapon_num == 1)
		{
			--remaining_bullet;
		}
	}
}

/**
* @brief UI�̕`��
*/
void Player::UiRender()
{
	//����UI�̕`��
	which_weapon_ui[0].Render(
		Transform({ WINDOW_WIDTH / 2 - 592 * ui_size / 2,-WINDOW_HEIGHT / 2 + 592 * ui_size / 2,-10 },
			saki::vector3_zero<float>, Vec3{ ui_size,ui_size,1 }), false);
	which_weapon_ui[1].Render(
		Transform({ -WINDOW_WIDTH / 2 + 592 * ui_size / 2,-WINDOW_HEIGHT / 2 + 592 * ui_size / 2,-11 },
			saki::vector3_zero<float>, Vec3{ ui_size,ui_size,1 }), false);
	//�eUI�̐F�̐ݒ�
	float r = 0.0f, g = 0.0f, b = 0.0f;
	if (remaining_bullet <= max_bullet / 2)
	{
		r = 1.0f;
		if (remaining_bullet > max_bullet / 5)
		{
			g = 1.0f;
		}
	}
	static constexpr Vec3 bullet_base_pos{ -700,-500,0 };
	//�eUI�̕`��
	//�c��e��
	if (remaining_bullet >= 10)
	{
		bullet_ui[remaining_bullet / 10].ColorChange(r, g, b, 1.0f);
		bullet_ui[remaining_bullet / 10].Render(
			Transform({ Vec3{30 * bullet_ui_scale * 0,0,-12}+bullet_base_pos,
				saki::vector3_zero<float>,Vec3{bullet_ui_scale,bullet_ui_scale,1} }),
			false);
	}
	bullet_ui[remaining_bullet % 10].ColorChange(r, g, b, 1.0f);
	bullet_ui[remaining_bullet % 10].Render(
		Transform({ Vec3{30 * bullet_ui_scale * 1,0,-13 }+bullet_base_pos,
			saki::vector3_zero<float>, Vec3{bullet_ui_scale,bullet_ui_scale,1} }),
		false);
	//�X���b�V��
	slash_ui.Render(
		Transform({ Vec3{30 * bullet_ui_scale * 2,0 ,-14}+bullet_base_pos,
			saki::vector3_zero<float>, Vec3{bullet_ui_scale,bullet_ui_scale,1} }),
		false);
	//�ő�e��
	if constexpr (max_bullet >= 10)
	{
		bullet_ui[max_bullet / 10].ColorChange(0.0f, 0.0f, 0.0f, 1.0f);
		bullet_ui[max_bullet / 10].Render(
			Transform({ Vec3{30 * bullet_ui_scale * 3,0,-15}+bullet_base_pos,
				saki::vector3_zero<float>, Vec3{bullet_ui_scale,bullet_ui_scale,1} }),
			false);
	}
	bullet_ui[max_bullet % 10].ColorChange(0.0f, 0.0f, 0.0f, 1.0f);
	bullet_ui[max_bullet % 10].Render(
		Transform({ Vec3{30 * bullet_ui_scale * 4,0,-16}+bullet_base_pos,
			saki::vector3_zero<float>, Vec3{bullet_ui_scale,bullet_ui_scale,1} }),
		false);
}