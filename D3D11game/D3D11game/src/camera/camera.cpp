#include "camera.h"
void Camera::SetPos(const Vec3& v3)
{
	eye = Vec4(v3.x, v3.y, v3.z, 0);
}
Vec3 Camera::GetPos()const
{
	return Vec3(eye.x, eye.y, eye.z);
}
void Camera::update()
{
	if (target != nullptr)
	{
		auto pos = GetPos();
		auto dist = target->transform.get_pos().x - pos.x;
		SetPos(pos + Vec3(camera_speed*dist / half_range, 0, 0));
	}
	if (eye.x < WINDOW_WIDTH / 2)eye.x = WINDOW_WIDTH / 2;
	if (vibration_power <= 0.0f)
	{
		eye.y = 0;
	}
	else
	{
		eye.y = ((up_flg) ? vibration_power : -vibration_power);
		vibration_power *= 0.5f;
		if (vibration_power < 0.1f)
		{
			vibration_power = 0.0f;
			vib_count = 0;
		}
		else if (++vib_count > 10)
		{
			up_flg = !up_flg;
			vib_count = 0;
		}
	}
	eye.z = -10000;
	focus = Vec4{ eye.x,eye.y,0.0f,eye.w };
	maView = DirectX::XMMatrixLookAtLH
	(Vector{ eye.x,eye.y,eye.z,eye.w }, Vector{ focus.x,focus.y,focus.z,focus.w }, Vector{ up.x,up.y,up.z,up.w });
	static constexpr float WINDOW_ASPECT = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);
	maProj = DirectX::XMMatrixPerspectiveFovLH(fov, WINDOW_ASPECT, NEAR_Z, FAR_Z);
	maProj = DirectX::XMMatrixOrthographicLH(WINDOW_WIDTH, WINDOW_HEIGHT, NEAR_Z, FAR_Z);
}

void Camera::move(const Vec4& new_eye)
{
	eye += new_eye;
}

void Camera::lookat(const Vec4& new_focus)
{
	focus = new_focus;
}