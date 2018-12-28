#include "keyboard_input.h"


HRESULT KeyboardInput::KeyboardInit(HWND hWnd)
{
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		Comment(L"DirectInput�̍쐬�Ɏ��s", L"keyboard_input.cpp");
		return E_FAIL;
	}
	if (FAILED(pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
	{
		Comment(L"�f�o�C�X�̍쐬�Ɏ��s", L"keyboard_input.cpp");
		return E_FAIL;
	}
	if (FAILED(pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		Comment(L"�f�[�^�t�H�[�}�b�g�̃Z�b�g�Ɏ��s", L"keyboard_input.cpp");
		return E_FAIL;
	}
	if (FAILED(pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		Comment(L"�������x���̃Z�b�g�Ɏ��s", L"keyboard_input.cpp");
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
		Comment(L"�f�o�C�X�̎擾�Ɏ��s", L"keyboard_input.cpp");
		return E_FAIL;
	}
	BYTE temp_diks[256];
	if (FAILED(pKeyDevice->GetDeviceState(sizeof(temp_diks), &temp_diks)))
	{
		Comment(L"�f�o�C�X���̎擾�Ɏ��s", L"keyboard_input.cpp");
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
	// �L�[�{�[�h�f�o�C�X�ւ̃A�N�Z�X���J��
	if (pKeyDevice)
		pKeyDevice->Unacquire();

	// �L�[�{�[�h�f�o�C�X�J��
	pKeyDevice->Release();
	pKeyDevice = NULL;
	// DirectInput�I�u�W�F�N�g�J��
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