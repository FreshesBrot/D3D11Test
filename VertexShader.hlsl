struct VSOut {
	
	float3 color : Color;
	float2 tex : TEXCOORD;
	float4 pos: SV_Position;

};

cbuffer Matrices {
	matrix m_transform;
};

VSOut main(float3 pos : Position, float3 color : Color, float2 tex : TexCord) {

	VSOut vsOut;
	vsOut.pos = float4(pos, 1.0f);
	vsOut.pos = mul(m_transform, vsOut.pos);
	vsOut.color = color;
	vsOut.tex = tex;
	return vsOut;
}