
float4 main(float3 color : Color, float2 UV : TexCoord, float3 normal : Normal) : SV_TARGET{
	normal = normalize(normal);
	return float4(normal, 1.0f);
}