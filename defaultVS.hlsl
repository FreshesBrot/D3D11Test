

cbuffer Matrices : register (b0) {
	matrix m_world;
	matrix m_view;
	matrix m_projection;
}

float4 main(float3 pos : POSITION) : SV_Position {
	matrix modelview = mul(m_world,m_projection);
	matrix projection = mul(modelview, m_projection);
	return mul(projection, float4(pos, 1.0f));
}