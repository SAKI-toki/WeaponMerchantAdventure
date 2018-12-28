#pragma once
#include "../common/common.h"
#include <saki/singleton/singleton.h>

class Device :public saki::Singleton<Device>
{
public:
	HRESULT init(HWND);
	void clear_screen();
	void draw_begin()
	{
		clear_screen();
	}
	void draw_end()
	{
		swap_chain->Present(1, 0);
	}

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> immediate_context;
	ComPtr<IDXGISwapChain> swap_chain;
	ComPtr<ID3D11RenderTargetView> render_target_view;
	ComPtr<ID3D11DepthStencilView> depth_stencil_view;
	ComPtr<ID3D11Texture2D> depth_stencil_texture;
};