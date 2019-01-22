/**
* @file arrow.cpp
* @brief 遠距離武器クラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/18
*/
#include "arrow.h"
#include "../../../input/gamepad/gamepad_input.h"
#include <saki/math/degree_radian_conversion.h>

/**
* @brief 武器用の初期化
*/
void Arrow::WeaponStart()
{
	current_delay = delay;
}

/**
* @brief 攻撃
* @param right 右かどうか
* @param pos 弾を発射する位置
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
* @brief 武器の更新
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
	//弾の更新
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
	//音の更新
	auto sound_itr = std::begin(sound);
	while (sound_itr != std::end(sound))
	{
		//再生終了していたらイテレーターを削除
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
* @brief 武器の描画
* @param t 描画位置
*/
void Arrow::WeaponRender(const Transform&)
{
	if (!weapon_enabled)return;
	//弾の描画
	for (auto&& n : bullet)
	{
		n.Render();
	}
}

/**
* @brief 武器の破棄
*/
void Arrow::WeaponDestroy()
{
	bullet.clear();
}

/**
* @brief 弾が当たったときに実行する関数
*/
void Arrow::CollisionBullet()
{
	sound.push_back(Sound());
	sound[sound.size() - 1].init(std::string("bullet_collision"), L"sample2.wav", false, true);
}
