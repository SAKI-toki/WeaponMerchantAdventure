#include "sprite.h"
#include "../device/device.h"
#include "../camera/camera.h"
int Sprite::depth = 9999;
bool Sprite::has_target = false;
float Sprite::target_x = 0;

HRESULT Sprite::Init(const std::string& texture_name, const WCHAR* texture_path, Vec2& size,
	const std::string& shader_name, const WCHAR* v_shader_path, const WCHAR* p_shader_path,
	const float slice_h_num, const float slice_v_num, const float slice_h_init, const float slice_v_init)
{
	size /= 2;
	texture_size = size;
	slice_num.x = slice_h_num, slice_num.y = slice_v_num;
	current_slice.x = slice_h_init, current_slice.y = slice_v_init;
	prev_slice = current_slice;
	//四角形
	/*
	Vec3(-0.5f,-0.5f,0),Vec2(0,1),
	Vec3(-0.5f,0.5f,0),Vec2(0,0),
	Vec3(0.5f,-0.5f,0),Vec2(1,1),
	Vec3(0.5f,0.5f,0),Vec2(1,0),
	*/
	Vertex vertices[] =
	{
		Vec3(-texture_size.x,-texture_size.y,0),
		Vec2((current_slice.x - 1) / slice_num.x,(current_slice.y - 0) / slice_num.y),
		Vec3(-texture_size.x,texture_size.y,0),
		Vec2((current_slice.x - 1) / slice_num.x,(current_slice.y - 1) / slice_num.y),
		Vec3(texture_size.x,-texture_size.y,0),
		Vec2((current_slice.x - 0) / slice_num.x,(current_slice.y - 0) / slice_num.y),
		Vec3(texture_size.x,texture_size.y,0),
		Vec2((current_slice.x - 0) / slice_num.x,(current_slice.y - 1) / slice_num.y),
	};

	//頂点バッファの作成
	{
		D3D11_BUFFER_DESC vb_desc;
		vb_desc.ByteWidth = sizeof(vertices);
		vb_desc.Usage = D3D11_USAGE_DEFAULT;
		vb_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vb_desc.CPUAccessFlags = 0;
		vb_desc.MiscFlags = 0;
		vb_desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vr_data;
		vr_data.pSysMem = vertices;
		vr_data.SysMemPitch = 0;
		vr_data.SysMemSlicePitch = 0;

		if (FAILED(Device::getinstance()->device->CreateBuffer(&vb_desc, &vr_data, vertex_buffer.GetAddressOf())))
		{
			Comment(L"頂点バッファの作成に失敗", L"sprite.cpp");
			return E_FAIL;
		}
	}
	//テクスチャ
	{
		if (FAILED(texture.load_texture(texture_name, texture_path)))
		{
			return E_FAIL;
		}
	}
	ComPtr<ID3DBlob> vertex_blob;
	ComPtr<ID3DBlob> pixel_blob;

	//シェーダーの読み込み
	if (FAILED(shader.load_shader(shader_name, v_shader_path, p_shader_path, vertex_blob, pixel_blob)))
	{
		return E_FAIL;
	}

	//定数バッファの作成
	{
		D3D11_BUFFER_DESC cb_desc;
		cb_desc.ByteWidth = sizeof(Constant);
		cb_desc.Usage = D3D11_USAGE_DYNAMIC;
		cb_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb_desc.MiscFlags = 0;
		cb_desc.StructureByteStride = 0;

		if (FAILED(Device::getinstance()->device->CreateBuffer(&cb_desc, NULL, constant_buffer.GetAddressOf())))
		{
			Comment(L"定数バッファの作成に失敗", L"sprite.cpp");
			return E_FAIL;
		}
	}
	//ブレンドステート
	{
		D3D11_BLEND_DESC bd;
		SecureZeroMemory(&bd, sizeof(bd));
		bd.IndependentBlendEnable = false;
		bd.AlphaToCoverageEnable = false;
		bd.RenderTarget[0].BlendEnable = true;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		if (FAILED(Device::getinstance()->device->CreateBlendState(&bd, blend_state.GetAddressOf())))
		{
			Comment(L"ブレンドステートの作成に失敗", L"sprite.cpp");
			return E_FAIL;
		}
	}
	//サンプラーステート
	{
		D3D11_SAMPLER_DESC sd;
		SecureZeroMemory(&sd, sizeof(sd));
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		if (FAILED(Device::getinstance()->device->CreateSamplerState(&sd, sampler_state.GetAddressOf())))
		{
			MessageBox(0, L"SamplerStateの生成に失敗しました ", L"sprite.cpp", MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}

void Sprite::Render(const Transform& transform, const bool camera_affected)
{
	if (has_target&&camera_affected&&std::abs(target_x - transform.get_pos().x) > WINDOW_WIDTH + 200)
	{
		return;
	}
	//頂点
	if (prev_slice != current_slice)
	{
		prev_slice = current_slice;
		//四角形
		/*
		Vec3(-0.5f,-0.5f,0),Vec2(0,1),
		Vec3(-0.5f,0.5f,0),Vec2(0,0),
		Vec3(0.5f,-0.5f,0),Vec2(1,1),
		Vec3(0.5f,0.5f,0),Vec2(1,0),
		*/
		Vertex vertices[] =
		{
			Vec3(-texture_size.x,-texture_size.y,0),
			Vec2((current_slice.x - 1) / slice_num.x,(current_slice.y - 0) / slice_num.y),

			Vec3(-texture_size.x,texture_size.y,0),
			Vec2((current_slice.x - 1) / slice_num.x,(current_slice.y - 1) / slice_num.y),

			Vec3(((is_ui_image) ? -texture_size.x + texture_size.x * 2 * percent : texture_size.x),-texture_size.y,0),
			Vec2((current_slice.x - 0) / slice_num.x,(current_slice.y - 0) / slice_num.y),

			Vec3(((is_ui_image) ? -texture_size.x + texture_size.x * 2 * percent : texture_size.x),texture_size.y,0),
			Vec2((current_slice.x - 0) / slice_num.x,(current_slice.y - 1) / slice_num.y),
		};

		//頂点バッファの作成
		{
			D3D11_BUFFER_DESC vb_desc;
			vb_desc.ByteWidth = sizeof(vertices);
			vb_desc.Usage = D3D11_USAGE_DEFAULT;
			vb_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vb_desc.CPUAccessFlags = 0;
			vb_desc.MiscFlags = 0;
			vb_desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA vr_data;
			vr_data.pSysMem = vertices;
			vr_data.SysMemPitch = 0;
			vr_data.SysMemSlicePitch = 0;

			if (FAILED(Device::getinstance()->device->CreateBuffer(&vb_desc, &vr_data, vertex_buffer.GetAddressOf())))
			{
				Comment(L"頂点バッファの作成に失敗", L"sprite.cpp");
			}
		}
	}
	else if (is_ui_image)
	{
		//四角形
		/*
		Vec3(-0.5f,-0.5f,0),Vec2(0,1),
		Vec3(-0.5f,0.5f,0),Vec2(0,0),
		Vec3(0.5f,-0.5f,0),Vec2(1,1),
		Vec3(0.5f,0.5f,0),Vec2(1,0),
		*/
		Vertex vertices[] =
		{
			Vec3(-texture_size.x,-texture_size.y,0),
			Vec2((current_slice.x - 1) / slice_num.x,(current_slice.y - 0) / slice_num.y),

			Vec3(-texture_size.x,texture_size.y,0),
			Vec2((current_slice.x - 1) / slice_num.x,(current_slice.y - 1) / slice_num.y),

			Vec3(((is_ui_image) ? -texture_size.x + texture_size.x * 2 * percent : texture_size.x),-texture_size.y,0),
			Vec2((current_slice.x - 0) / slice_num.x,(current_slice.y - 0) / slice_num.y),

			Vec3(((is_ui_image) ? -texture_size.x + texture_size.x * 2 * percent : texture_size.x),texture_size.y,0),
			Vec2((current_slice.x - 0) / slice_num.x,(current_slice.y - 1) / slice_num.y),
		};

		//頂点バッファの作成
		{
			D3D11_BUFFER_DESC vb_desc;
			vb_desc.ByteWidth = sizeof(vertices);
			vb_desc.Usage = D3D11_USAGE_DEFAULT;
			vb_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vb_desc.CPUAccessFlags = 0;
			vb_desc.MiscFlags = 0;
			vb_desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA vr_data;
			vr_data.pSysMem = vertices;
			vr_data.SysMemPitch = 0;
			vr_data.SysMemSlicePitch = 0;

			if (FAILED(Device::getinstance()->device->CreateBuffer(&vb_desc, &vr_data, vertex_buffer.GetAddressOf())))
			{
				Comment(L"頂点バッファの作成に失敗", L"sprite.cpp");
			}
		}
	}
	//定数バッファ
	{
		D3D11_MAPPED_SUBRESOURCE p_data;
		SecureZeroMemory(&p_data, sizeof(p_data));
		Constant c;
		SecureZeroMemory(&c, sizeof(c));
		//ワールド行列
		auto world = DirectX::XMMatrixIdentity();
		//拡縮
		auto transform_scale = transform.get_scale();
		auto scale = DirectX::XMMatrixScaling(transform_scale.x, transform_scale.y, transform_scale.z);
		//回転
		auto transform_rotation = transform.get_rot();
		auto rotation = DirectX::XMMatrixRotationRollPitchYaw(transform_rotation.x, transform_rotation.y, transform_rotation.z);
		//位置
		auto transform_position = transform.get_pos();
		if (!camera_affected)transform_position +=
			Vec3(Camera::getinstance()->GetPos().x, Camera::getinstance()->GetPos().y, 0);
		auto translation = DirectX::XMMatrixTranslation(transform_position.x, transform_position.y, /*transform_position.z*/static_cast<float>(depth--));
		world = scale * rotation * translation;
		if (SUCCEEDED(Device::getinstance()->immediate_context->
			Map(constant_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &p_data)))
		{
			auto m = world * Camera::getinstance()->maView * Camera::getinstance()->maProj;
			m = DirectX::XMMatrixTranspose(m);
			c.wvp = m;
			c.color = color;
			memcpy_s(p_data.pData, p_data.RowPitch, (void*)(&c), sizeof(c));
			Device::getinstance()->immediate_context->
				Unmap(constant_buffer.Get(), 0);
		}
	}

	shader.set_shader();
	texture.set_texture();
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	Device::getinstance()->immediate_context->
		IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), &stride, &offset);
	Device::getinstance()->immediate_context->
		IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	Device::getinstance()->immediate_context->
		VSSetConstantBuffers(0, 1, constant_buffer.GetAddressOf());
	Device::getinstance()->immediate_context->
		PSSetConstantBuffers(0, 1, constant_buffer.GetAddressOf());
	Device::getinstance()->immediate_context->
		PSSetSamplers(0, 1, sampler_state.GetAddressOf());
	UINT color_key = 0xffffffff;
	Device::getinstance()->immediate_context->
		OMSetBlendState(blend_state.Get(), 0, color_key);
	Device::getinstance()->immediate_context->
		Draw(4, 0);
	Device::getinstance()->immediate_context->
		OMSetBlendState(0, 0, color_key);
}
