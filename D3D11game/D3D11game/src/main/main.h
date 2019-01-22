#pragma once
#include "../common/common.h"
#include <saki/singleton/singleton.h>
class Main:public saki::Singleton<Main>
{
public:
	HRESULT init_window(HINSTANCE, int);

	HWND hwnd;
	HINSTANCE hinst;
};