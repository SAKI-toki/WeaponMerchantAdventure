Texture2D Texture:register(t0);
SamplerState Sampler:register(s0);

cbuffer global
{
	matrix wvp;
	float4 diffuse;
};

struct VsOutput
{
	float4 pos:SV_POSITION;
	float2 Uv:TEXCOORD;
};

//���_�V�F�[�_�[
VsOutput vs(float4 POS:POSITION, float2 UV : TEXCOORD)
{
	VsOutput output = (VsOutput)0;
	output.pos = mul(POS, wvp);
	output.Uv = UV;
	return output;
}

//�s�N�Z���V�F�[�_�[
float4 ps(VsOutput output) :SV_Target
{
	return diffuse * Texture.Sample(Sampler, output.Uv);
}