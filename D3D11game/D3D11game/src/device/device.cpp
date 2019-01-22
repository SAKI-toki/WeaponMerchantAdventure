#include "device.h"
#include "../input/keyboard/keyboard_input.h"

HRESULT Device::init(HWND hwnd)
{
	// デバイスとスワップチェーンの作成
	{
		DXGI_SWAP_CHAIN_DESC sd;
		SecureZeroMemory(&sd, sizeof(sd));

		sd.BufferCount = 1;
		sd.BufferDesc.Width = WINDOW_WIDTH;
		sd.BufferDesc.Height = WINDOW_HEIGHT;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = FPS;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;
		sd.Windowed = !FULL_SCREEN;

		D3D_FEATURE_LEVEL feature_levels = D3D_FEATURE_LEVEL_11_0;

		if (FAILED(D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0,
			0, &feature_levels, 1, D3D11_SDK_VERSION, &sd, swap_chain.GetAddressOf(), device.GetAddressOf(),
			0, immediate_context.GetAddressOf())))
		{
			Comment(L"SwapChainの作成に失敗", L"DeviceManager.cpp");
			return E_FAIL;
		}
	}

	//レンダーターゲットビューの作成
	{
		ComPtr<ID3D11Texture2D> back_buffer;
		if (FAILED(swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)back_buffer.GetAddressOf())))
		{
			Comment(L"バッファの取得に失敗", L"DeviceManager.cpp");
			return E_FAIL;
		}
		if (FAILED(device->CreateRenderTargetView(back_buffer.Get(), NULL, render_target_view.GetAddressOf())))
		{
			Comment(L"レンダーターゲットビューの作成に失敗", L"DeviceManager.cpp");
			return E_FAIL;
		}
	}

	//深度ステンシルビューの作成
	{
		D3D11_TEXTURE2D_DESC tex_desc;
		SecureZeroMemory(&tex_desc, sizeof(tex_desc));
		tex_desc.Width = WINDOW_WIDTH;
		tex_desc.Height = WINDOW_HEIGHT;
		tex_desc.MipLevels = 1;
		tex_desc.ArraySize = 1;
		tex_desc.Format = DXGI_FORMAT_D32_FLOAT;
		tex_desc.SampleDesc.Count = 1;
		tex_desc.Usage = D3D11_USAGE_DEFAULT;
		tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		tex_desc.CPUAccessFlags = 0;
		tex_desc.MiscFlags = 0;
		if (FAILED(device->CreateTexture2D(&tex_desc, NULL, depth_stencil_texture.GetAddressOf())))
		{
			Comment(L"深度ステンシルバッファ用のテクスチャの作成に失敗", L"DeviceManager.cpp");
			return E_FAIL;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC ds_desc;
		SecureZeroMemory(&ds_desc, sizeof(ds_desc));
		ds_desc.Format = tex_desc.Format;
		ds_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		ds_desc.Texture2D.MipSlice = 0;
		if (FAILED(device->CreateDepthStencilView(depth_stencil_texture.Get(), &ds_desc, depth_stencil_view.GetAddressOf())))
		{
			Comment(L"テクスチャリソースからビューの作成に失敗", L"DeviceManager.cpp");
			return E_FAIL;
		}
	}
	//レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	{
		immediate_context->OMSetRenderTargets(1, render_target_view.GetAddressOf(), depth_stencil_view.Get());
	}
	//ビューポートの設定
	{
		D3D11_VIEWPORT vp;
		SecureZeroMemory(&vp, sizeof(vp));
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		vp.Width = WINDOW_WIDTH;
		vp.Height = WINDOW_HEIGHT;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		immediate_context->RSSetViewports(1, &vp);
	}
	//ラスタライズ設定
	{
		D3D11_RASTERIZER_DESC rdc;
		SecureZeroMemory(&rdc, sizeof(rdc));
		rdc.CullMode = D3D11_CULL_NONE;
		rdc.FillMode = D3D11_FILL_SOLID;
		rdc.FrontCounterClockwise = false;

		ComPtr<ID3D11RasterizerState> pir = nullptr;
		if (FAILED(device->CreateRasterizerState(&rdc, pir.GetAddressOf())))
		{
			Comment(L"ラスタライザの設定に失敗", L"device.cpp");
			return E_FAIL;
		}
		immediate_context->RSSetState(pir.Get());
	}
	//キーボードの初期化
	if (FAILED(KeyboardInput::getinstance()->KeyboardInit(hwnd)))
	{
		return E_FAIL;
	}
	return S_OK;
}

void Device::clear_screen()
{
	float clearColor[4] = { 0,0,0,1.0f };
	immediate_context->OMSetRenderTargets(1, render_target_view.GetAddressOf(), depth_stencil_view.Get());
	immediate_context->ClearRenderTargetView(render_target_view.Get(), clearColor);
	immediate_context->ClearDepthStencilView(depth_stencil_view.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}