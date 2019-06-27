
cbuffer Matrix {
	matrix m_transform;
};

float4 main(float3 pos : POSITION) : SV_Position{
	return mul(m_transform,float4(pos,1.0f));
}