/**
* @file arrow.cpp
* @brief 遠距離武器クラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/18
*/
#include "arrow.h"
#include "../../../input/gamepad/gamepad_input.h"
#include "../../../common/saki/degree_radian/degree_radian_conversion.h"

/**
* @brief コンストラクタ
*/
Arrow::Arrow()
{
	sprite.Init(std::string("arrow"), L"arrow.png",  32, 64, 1, 0, 0, 1.0f);
}

/**
* @brief 武器用の初期化
*/
void Arrow::WeaponStart()
{
	current_delay = delay;
}

/**
* @brief 攻撃
* @param pos 弾を発射する位置
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
* @brief 武器の更新
*/
void Arrow::WeaponUpdate(const VEC2&, bool)
{
	if (current_delay < delay) { ++current_delay; }
	//右スティックの角度
	float stick_x = GamepadInput::GetInstance()->GetStick(true, true);
	float stick_y = GamepadInput::GetInstance()->GetStick(true, false);
	//右スティックが倒れているとき
	if (stick_x != 0.0f || stick_y != 0.0f)
	{
		//上を向いているときを0度となるように計算する
		stick_angle = std::atan2f(-stick_y, stick_x) + saki::to_radian<float>(90.0f);
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
* @brief 武器の描画
* @param t 描画位置
*/
void Arrow::WeaponRender(const Transform& t)
{
	if (!weapon_enabled)return;
	if (current_delay >= delay)
	{	
		//矢印の描画
		sprite.Render(Transform(t.pos, stick_angle, 1));
	}
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
	sound[sound.size() - 1].Init(std::string("bullet_collision"), L"sample2.wav", false, true);
}