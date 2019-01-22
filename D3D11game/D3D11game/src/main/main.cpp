#include "main.h"
#include "../device/device.h"
#include "../scene/manager/scene_manager.h"
#include "../input/gamepad/gamepad_input.h"
#include "../input/keyboard/keyboard_input.h"
#include "../sound/manager/sound_manager.h"

//関数プロトタイプの宣言
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void MessageLoop();

//エントリー関数
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	if (FAILED(Main::getinstance()->init_window(hInstance, nCmdShow)))
	{
		return 0;
	}
	if (FAILED(Device::getinstance()->init(Main::getinstance()->hwnd)))
	{
		return 0;
	}
	if (FAILED(SoundManager::getinstance()->init()))
	{
		return 0;
	}
	SceneManager::getinstance()->Init();
	MessageLoop();
	SceneManager::getinstance()->Destroy();
	return 0;
}

//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

//メッセージループ
void MessageLoop()
{
	MSG msg = MSG();
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			GamepadInput::getinstance()->Update();
			if (FAILED(KeyboardInput::getinstance()->Update()))
			{
				return;
			}
			SceneManager::getinstance()->Update();
			SceneManager::getinstance()->Render();
		}
	}
}
HRESULT Main::init_window(HINSTANCE hInst, int nCmd)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinst;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = APP_NAME;
	wcex.hIconSm = wcex.hIcon;

	if (!RegisterClassEx(&wcex))
	{
		Comment(L"ウィンドウ登録に失敗", L"Main.cpp");
		return E_FAIL;
	}

	hinst = hInst;
	hwnd = CreateWindowEx(WS_EX_ACCEPTFILES, APP_NAME, APP_NAME, FULL_SCREEN ? WS_VISIBLE | WS_POPUP : WS_OVERLAPPEDWINDOW,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, hinst, 0);

	if (!hwnd)
	{
		Comment(L"ウィンドウ生成に失敗", L"Main.cpp");
		return E_FAIL;
	}

	ShowWindow(hwnd, nCmd);
	UpdateWindow(hwnd);

	return S_OK;
}

void ExitGame()
{
	PostQuitMessage(0);
}