#pragma once
#include "../common/common.h"
#include "../object/base/object_base.h"
#include <saki/singleton/singleton.h>
#include <saki/math/degree_radian_conversion.h>

class Camera :public saki::Singleton<Camera>
{
	static constexpr float camera_speed = 7.0f;
	static constexpr float half_range = 100.0f;
	//追尾させるターゲット
	ObjectBase* target = nullptr;
	float RIGHT_LIMIT;
	float vibration_power = 0.0f;
	bool up_flg = false;
	size_t vib_count = 0;
	Vec4
		eye{ 0.0f,0.0f,-10000.0f,0.0f },
		focus{ 0.0f,0.0f,0.0f,0.0f },
		up{ 0.0f,1.0f,0.0f,0.0f }
	;
	//視野角(radian)
	static constexpr float fov = saki::to_radian<float>(FOV);

public:
	void SetPos(const Vec3&);
	Vec3 GetPos()const;
	/**
	* brief ターゲットのセット
	*/
	void SetTarget(ObjectBase* t)
	{
		target = t;
	}
	void DirectSetPos(const Vec4& v4)
	{
		eye = v4;
	}
	/**
	* @brief カメラの振動の強さをセット
	* @param power 振動の強さ
	*/
	void SetVibration(const float power)
	{
		vibration_power = power;
	}
	Matrix maView, maProj;
	void update();
	void move(const Vec4&);
	void lookat(const Vec4&);
};