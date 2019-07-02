struct VSOut {
	
	float3 color : Color;
	float2 tex : TexCoord;
	float3 normal : Normal;
	float4 pos: SV_Position;

};

cbuffer Matrices : register (b0) {
	matrix m_transform;
	matrix m_projection;
};

VSOut main(float3 pos : Position, float3 color : Color, float3 normal : Normal, float2 tex : TexCoord) {

	VSOut vsOut;
	vsOut.pos = float4(pos, 1.0f);
	
	matrix projection = mul(m_projection, m_transform);
	vsOut.pos = mul(projection, vsOut.pos);
	
	vsOut.color = color;
	vsOut.normal = mul(projection, normal);
	vsOut.tex = tex;
	return vsOut;
}