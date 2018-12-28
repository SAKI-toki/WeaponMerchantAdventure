#pragma once
#include "../../common/common.h"
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include <saki/singleton/singleton.h>
#define DIRECTINPUT_VERSION 0x0800

class KeyboardInput :public saki::Singleton<KeyboardInput>
{
	LPDIRECTINPUT8 pDinput;
	LPDIRECTINPUTDEVICE8 pKeyDevice;
	BYTE old_diks[256];
	BYTE current_diks[256];
	void Destroy();
public:
	HRESULT KeyboardInit(HWND);
	HRESULT Update();
	bool GetKey(int);
	bool GetKeyDown(int);
	bool GetKeyUp(int);
	~KeyboardInput()
	{
		Destroy();
	}
};