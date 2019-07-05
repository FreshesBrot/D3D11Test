Texture2D tex : register(t0);
SamplerState smplr : register(s0);

cbuffer Light : register (b0) {

}

cbuffer Material : register (b1) {
	struct {
		float r, g, b;
	} color;
	struct {
		float s, d, n;
	} reflection;
}

float4 main(float3 color : Color, float2 UV : TexCoord, float3 NRM : normal) : SV_TARGET{
	return tex.Sample(smplr,UV);
}