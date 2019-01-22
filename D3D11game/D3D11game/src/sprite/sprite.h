#pragma once
#include "../common/common.h"
#include "../shader/shader.h"
#include "../texture/texture.h"
class Sprite
{
	Shader shader;
	Texture texture;
	ComPtr<ID3D11Buffer> vertex_buffer;
	ComPtr<ID3D11Buffer> constant_buffer;
	ComPtr<ID3D11BlendState> blend_state;
	ComPtr<ID3D11SamplerState> sampler_state;
	//í∏ì_ÇÃç\ë¢ëÃ
	struct Vertex
	{
		Vec3 vertex_pos;
		Vec2 tex;
	};
	//íËêîÇÃç\ë¢ëÃ
	struct Constant
	{
		Matrix wvp;
		Vec4 color;
	};
	Vec4 color{ 1,1,1,1 };
public:
	HRESULT Init(const std::string&, const WCHAR*, Vec2&,
		const std::string& = "shader", const WCHAR* = L"sprite_shader.hlsl", 
		const WCHAR* = L"sprite_shader.hlsl",
		const float = 1, const float = 1, const float = 1, const float = 1);
	void Render(const Transform&, const bool = true);
	void ColorChange(const float r, const float g, const float b, const float a)
	{
		color.x = r, color.y = g, color.z = b, color.w = a;
	}
	Vec2 slice_num;
	Vec2 prev_slice;
	Vec2 current_slice;
	Vec2 texture_size;
	bool is_ui_image = false;
	float percent = 1.0f;
	static int depth;
	static bool has_target;
	static float target_x;
};