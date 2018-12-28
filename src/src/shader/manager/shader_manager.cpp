#include "shader_manager.h"
#include "../../device/device.h"
extern void ExitGame();

HRESULT ShaderManager::load_shader(const std::string& key, const WCHAR* vertex_path, const WCHAR* pixel_path,
	ComPtr<ID3DBlob>& v_blob, ComPtr<ID3DBlob>& p_blob)
{
	auto itr = shader_map.find(key);
	if (itr == end(shader_map))
	{
		WCHAR v_path[256], p_path[256];
		wcscpy_s(v_path, shader_path);
		wcscat_s(v_path, vertex_path);
		wcscpy_s(p_path, shader_path);
		wcscat_s(p_path, pixel_path);
		ComPtrShader comptr_shader;
		//�V�F�[�_�[�̃R���p�C��
		{
			if (FAILED(D3DCompileFromFile(
				v_path, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "vs", "vs_5_0", 
				D3DCOMPILE_ENABLE_STRICTNESS, 0, v_blob.GetAddressOf(), NULL)))
			{
				Comment(L"���_�V�F�[�_�[�̃R���p�C���Ɏ��s", L"shader_manager.cpp");
				return E_FAIL;
			}
			if (FAILED(D3DCompileFromFile(
				p_path, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "ps", "ps_5_0", 
				D3DCOMPILE_ENABLE_STRICTNESS, 0, p_blob.GetAddressOf(), NULL)))
			{
				Comment(L"�s�N�Z���V�F�[�_�[�̃R���p�C���Ɏ��s", L"shader_manager.cpp");
				return E_FAIL;
			}
		}
		//�V�F�[�_�[�I�u�W�F�N�g�̍쐬
		{
			if (FAILED(Device::getinstance()->device->CreateVertexShader(
				v_blob->GetBufferPointer(), v_blob->GetBufferSize(), 
				NULL, comptr_shader.vertex_shader.GetAddressOf())))
			{
				Comment(L"���_�V�F�[�_�[�I�u�W�F�N�g�̍쐬�Ɏ��s", L"shader_manager.cpp");
				return E_FAIL;
			}
			if (FAILED(Device::getinstance()->device->CreatePixelShader(
				p_blob->GetBufferPointer(), p_blob->GetBufferSize(), 
				NULL, comptr_shader.pixel_shader.GetAddressOf())))
			{
				Comment(L"�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̍쐬�Ɏ��s", L"shader_manager.cpp");
				return E_FAIL;
			}
		}
		//�C���v�b�g���C�A�E�g�̍쐬
		{
			D3D11_INPUT_ELEMENT_DESC vertex_desc[]{
			{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			if (FAILED(Device::getinstance()->device->CreateInputLayout(
				vertex_desc, ARRAYSIZE(vertex_desc),
				v_blob->GetBufferPointer(), v_blob->GetBufferSize(), 
				comptr_shader.input_layout.GetAddressOf())))
			{
				Comment(L"�C���v�b�g���C�A�E�g�̍쐬�Ɏ��s", L"shader_manager.cpp");
				return E_FAIL;
			}
		}
		shader_map.insert(std::make_pair(key, comptr_shader));
	}
	
	return S_OK;
}
void ShaderManager::set_shader(const std::string& key)
{
	auto itr = shader_map.find(key);
	if (itr == end(shader_map))
	{
		Comment(L"�o�^���Ă��Ȃ�shader���g�p���悤�Ƃ��Ă��܂�", L"shader_manager.cpp");
		ExitGame();
	}
	else
	{
		Device::getinstance()->immediate_context->
			VSSetShader(itr->second.vertex_shader.Get(), 0, 0);
		Device::getinstance()->immediate_context->
			PSSetShader(itr->second.pixel_shader.Get(), 0, 0);
		Device::getinstance()->immediate_context->
			IASetInputLayout(itr->second.input_layout.Get());
	}
}