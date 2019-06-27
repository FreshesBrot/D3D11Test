texture t1 : register(t0);

float4 main(float3 color : Color, float2 tex : TexCoord) : SV_TARGET {

	return float4(color,1.0f);

}