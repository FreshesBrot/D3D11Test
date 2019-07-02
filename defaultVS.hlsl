
cbuffer Matrix {
	matrix m_transform;
	matrix m_projection;
};

float4 main(float3 pos : POSITION) : SV_Position {
	matrix projection = mul(m_projection,m_transform);
return mul(projection, float4(pos, 1.0f));
}