#include "ui_image.h"
#include "../manager/ui_manager.h"


void UiImage::Init(const std::string& name, WCHAR* path, const LONG w, const LONG h, 
	const VEC2& pos, const float rot, const float scale)
{
	sprite.Init(name, path, w, h);
	transform.Init(pos, rot, scale);
	max_w = w, max_h = h;
	enabled = false;
	UiManager::getinstance()->SetUiImage(this);
}

void UiImage::Render()
{
	sprite.SetRect({ 0,0,static_cast<LONG>(max_w*percent),max_h });
	sprite.Render(transform, false, false);
}
