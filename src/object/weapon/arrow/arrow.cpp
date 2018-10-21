/**
* @file arrow.cpp
* @brief 遠距離武器クラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/18
*/
#include "arrow.h"
#include "../../../input/gamepad/gamepad_input.h"

/**
* @brief コンストラクタ
*/
Arrow::Arrow()
{
	sprite.Init(std::string("arrow"), L"arrow.png", true, 32, 64, 1, 0, 0, 1.0f);
}

/**
* @brief 攻撃
* @param pos 弾を発射する位置
*/
void Arrow::Attack(bool, const VEC2& pos)
{
	bullet.push_front(Bullet());
	
	std::begin(bullet)->Init("bullet", L"sample5.png", 32, 32, VEC2(pos.x, pos.y - 0.5f));
	std::begin(bullet)->BulletInit(stick_angle);
}

/**
* @brief 武器の更新
*/
void Arrow::WeaponUpdate(const VEC2&, bool)
{
	//右スティックの角度
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
}

/**
* @brief 武器の描画
* @param t 描画位置
*/
void Arrow::WeaponRender(const Transform& t)
{
	/*if (arrow_rendering)
	{*/
	//矢印の描画
		sprite.Render(Transform(t.pos, stick_angle, 1));
	/*}*/
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