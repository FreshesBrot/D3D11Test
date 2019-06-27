cbuffer Matrix {
	matrix m_transform;
};

float4 main( float3 pos : POSITION, float3 col : color ) : SV_POSITION {
	return mul(m_transform,float4(pos,1.0f));
}