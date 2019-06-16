struct VSOut {
	
	float3 color : Color;
	float4 pos: SV_Position;
};

cbuffer Matrices {
	matrix m_translate;
};

VSOut main(float2 pos : Position, float3 color : Color) {

	VSOut vsOut;
	vsOut.pos = float4(pos, 0.0f, 1.0f);
	vsOut.pos = mul(m_translate,vsOut.pos);
	vsOut.color = color;
	return vsOut;
}