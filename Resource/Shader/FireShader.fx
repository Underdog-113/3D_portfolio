float4x4 gWorldViewProjectionMatrix;
float4x4 gInvWorldMatrix;

float4x4 gWorld;
float4x4 gView;
float4x4 gProjection;

float4 gWorldLightPosition;

float  gSpeed;
float  gAlpha;

texture g_DiffuseTex;
sampler Diffuse = sampler_state
{
	Texture = <g_DiffuseTex>;
	FILTER = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

texture g_NoiseTex;
sampler NoiseTex = sampler_state
{
	Texture = <g_NoiseTex>;
	FILTER = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};


struct VS_INPUT
{
	float4 mPosition : POSITION;
	float3 mNormal	 : NORMAL;
	float2 mUV		 : TEXCOORD0;

};

struct VS_OUTPUT
{
	float4 mPosition : POSITION;
	float2 mUV		: TEXCOORD0;
	float3 mDiffuse : TEXCOORD1;

};

struct PS_OUTPUT
{
	float4 vColor  : COLOR0;
};


VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.mPosition = mul(Input.mPosition, gWorldViewProjectionMatrix);

	float4 objectLightPosition = mul(gWorldLightPosition, gInvWorldMatrix);
	float3 lightDir = normalize(Input.mPosition.xyz - objectLightPosition.xyz);

	Output.mDiffuse = dot(-lightDir, normalize(Input.mNormal));
	Output.mUV = Input.mUV;

	return Output;

}

struct PS_INPUT
{
	float2 mUV : TEXCOORD0;
	float3 mDiffuse : TEXCOORD1;
	float3 mNormal	 : NORMAL;

};

float4 ps_main(VS_OUTPUT Input) : COLOR
{
	// Base albedo Texture
	float4 albedo = tex2D(Diffuse, Input.mUV + float2(0, gSpeed));

	// Noise Texture
	float4 Noise = tex2D(NoiseTex, Input.mUV * albedo.r);

	// To disappear to match the noise texture
	float multiply1 = 0;
	float multiply2 = 0;	

	multiply1 = saturate((Noise.r * sin(gAlpha)) * 5.5f);
	multiply2 = saturate(Noise.r * sin(gAlpha));

	float multiple = pow(multiply1 + multiply2, 30);

	float3 diffuse = albedo.rgb;
	
	return float4(diffuse, multiple);
}

technique DissolveShader
{
	pass p0
	{
		CullMode = None;
		AlphaBlendEnable = true;
		DestBlend = InvsrcAlpha;
		SrcBlend = SrcAlpha;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}
};