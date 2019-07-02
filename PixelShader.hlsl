Texture2D tex : register(t0);
SamplerState smplr : register(s0);

float4 main(float3 color : Color, float2 UV : TexCoord, float3 NRM : normal) : SV_TARGET{
	return tex.Sample(smplr,UV);
}