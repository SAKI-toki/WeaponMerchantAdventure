#include "keyboard_input.h"


HRESULT KeyboardInput::KeyboardInit(HWND hWnd)
{
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		Comment(L"DirectInputの作成に失敗", L"keyboard_input.cpp");
		return E_FAIL;
	}
	if (FAILED(pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
	{
		Comment(L"デバイスの作成に失敗", L"keyboard_input.cpp");
		return E_FAIL;
	}
	if (FAILED(pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		Comment(L"データフォーマットのセットに失敗", L"keyboard_input.cpp");
		return E_FAIL;
	}
	if (FAILED(pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		Comment(L"協調レベルのセットに失敗", L"keyboard_input.cpp");
		return E_FAIL;
	}
	int i;
	for (i = 0; i < 0; ++i) {
		current_diks[i] = 0;
	}
	return S_OK;
}

HRESULT KeyboardInput::Update()
{
	if (FAILED(pKeyDevice->Acquire()))
	{
		Comment(L"デバイスの取得に失敗", L"keyboard_input.cpp");
		return E_FAIL;
	}
	BYTE temp_diks[256];
	if (FAILED(pKeyDevice->GetDeviceState(sizeof(temp_diks), &temp_diks)))
	{
		Comment(L"デバイス情報の取得に失敗", L"keyboard_input.cpp");
		return E_FAIL;
	}

	int i;
	for (i = 0; i < 256; ++i)
	{
		old_diks[i] = current_diks[i];
		current_diks[i] = temp_diks[i];
	}
	return S_OK;
}

void KeyboardInput::Destroy()
{
	// キーボードデバイスへのアクセス権開放
	if (pKeyDevice)
		pKeyDevice->Unacquire();

	// キーボードデバイス開放
	pKeyDevice->Release();
	pKeyDevice = NULL;
	// DirectInputオブジェクト開放
	pDinput->Release();
	pDinput = NULL;
}

bool KeyboardInput::GetKey(int key)
{
	return static_cast<bool>(current_diks[key] & 0x80);
}
bool KeyboardInput::GetKeyDown(int key)
{
	return static_cast<bool>(current_diks[key] & 0x80) && !static_cast<bool>(old_diks[key] & 0x80);
}
bool KeyboardInput::GetKeyUp(int key)
{
	return !static_cast<bool>(current_diks[key] & 0x80) && static_cast<bool>(old_diks[key] & 0x80);
}