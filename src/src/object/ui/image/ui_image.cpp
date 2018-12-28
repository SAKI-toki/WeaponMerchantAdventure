#include "ui_image.h"
#include "../manager/ui_manager.h"


void UiImage::Init(const std::string& name, WCHAR* path, const float w, const float h,
	const Vec3& pos, const Vec3& rot, const Vec3& scale)
{
	sprite.Init(name, path, Vec2(w, h));
	sprite.is_ui_image = true;
	transform.set_pos(pos);
	transform.set_rot(rot);
	transform.set_scale(scale);
	max_w = w, max_h = h;
	enabled = false;
	UiManager::getinstance()->SetUiImage(this);
}

void UiImage::Render()
{
	sprite.percent = percent;
	sprite.Render(transform, false);
}
