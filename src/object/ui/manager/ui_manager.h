#pragma once
#include "../image/ui_image.h"
#include "../../../common/saki/singleton/singleton.h"
#include <vector>

class UiManager :public saki::singleton<UiManager>
{
	std::vector<UiImage*> image_list;
public:
	void SetUiImage(UiImage* image)
	{
		image_list.push_back(image);
	}

	void Render()
	{
		for (auto&& i : image_list)
		{
			if (!(i->enabled))continue;
			i->Render();
		}
	}

	void Destroy()
	{
		image_list.clear();
	}
};