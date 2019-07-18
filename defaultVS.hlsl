struct VS {
	float4 pos : SV_Position;
	float3 color : Color;
};

cbuffer Matrices : register (b0) {
	matrix m_world;
	matrix m_view;
	matrix m_projection;
}

VS main(float3 pos : POSITION, float3 color : Color) {
	VS vs;
	matrix modelview = mul(m_view, m_world);
	matrix projection = mul(m_projection, modelview);
	vs.pos = mul(projection, float4(pos, 1.0f));
	vs.color = color;
	return vs;
}