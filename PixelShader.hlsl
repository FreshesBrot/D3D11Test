Texture2D tex : register(t0);
SamplerState smplr : register(s0);

cbuffer Light : register (b0) {
	float3 Ldir;
	float Lintensity;
	float4 Lcolor;
	float4 Lambient;
}

cbuffer Material : register (b1) {
	struct {
		float r, g, b;
	} color;
	float pad1;
	struct {
		float s, d, n;
	} reflection;
	float pad2;
}

float4 main(float3 color : Color, float2 UV : TexCoord, float3 normal : Normal) : SV_TARGET{
	//normalize transformed normals
	normal = normalize(normal);

	//light intensity
	float3 lighting = reflection.d * dot(normal, Ldir) * Lintensity;

	//texture color
	float4 textureColor = tex.Sample(smplr, UV);

	//lighted texture
	float3 ambientLighting = saturate(lighting + Lambient);
	
	//add ambient
	return float4(ambientLighting, 1);
}