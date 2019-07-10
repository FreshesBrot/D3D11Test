Texture2D tex : register(t0);
SamplerState smplr : register(s0);

cbuffer Light : register (b0) {
	float3 Ldir;
	float Lintensity;
	float3 Lcolor;
	float pad11;
	float3 Lambient;
	float pad12;
}

cbuffer Material : register (b1) {
	float3 Mcolor;
	float pad21;
	struct {
		float d, s;
		int n;
	} Mreflection;
	float pad22;
}

//power of function
float pow(float a, int n) {
	float exp = 1;
	for (int i = n; i > 0; i--) {
		exp *= a;
	}
	return exp;
}

//calculate lambertian diffuse
float lambertian(float3 normal) {
	return Mreflection.d * dot(Ldir, normal) * Lintensity;
}

//calculate specular lighting
float spec(float3 pos, float3 Lreflect) {
	float dotpr = dot(pos, Lreflect);
	float specExp = pow(dotpr, Mreflection.n);
	return Mreflection.s * specExp * Lintensity;
}


float4 main(float4 pos : SV_Position, float3 color : Color, float2 UV : TexCoord, float3 normal : Normal) : SV_TARGET{
	//normalize transformed normals
	normal = normalize(normal);

	//lambertian lighting
	float4 lambert = lambertian(normal);

	//specular
	float specular = spec(float3(pos.xyz), Ldir);
	
	//ambient
	float3 ambient = Lambient;
	
	//surface color
	float4 texColor = tex.Sample(smplr, UV);
	float3 CS = texColor * Mcolor;

	//reflection color
	float3 Cr = saturate(lambert * CS * Lcolor + specular * Lcolor + CS * Lambient);
	
	return float4(Cr,1);
}