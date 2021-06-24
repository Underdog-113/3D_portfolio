float4x4 gWorldViewProjectionMatrix;
float4x4 gInvWorldMatrix;

float4x4 gWorld;
float4x4 gView;
float4x4 gProjection;

float4 gWorldLightPosition;

float  gTime;
float  gAlpha;
float  m_defaultDissolveVal = 0.9f;

float3 gDissolveLineColor = float3(1,0,0);

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
	float4 albedo = tex2D(Diffuse, Input.mUV);

	// Noise Texture
	float4 Noise = tex2D(NoiseTex, Input.mUV);

	// To disappear to match the noise texture
	float multiply1 = saturate((Noise.r * sin(gAlpha)) * 5.5f);
	float multiply2 = saturate(Noise.r * sin(gAlpha));

	// Current Dissolve Line Value
	float CurrentDissolveVal = saturate(pow(multiply1 + multiply2, 20)); 
	
	// Returns the "multiply2" multiple of "multiply1"
	float multiple = pow(multiply1 + multiply2, 20);

	// Dissolve Line Size
	float3 DissolveLineSize;

	if (m_defaultDissolveVal >= CurrentDissolveVal)
	{
		DissolveLineSize = float3(100.f, 1.f, 1.f);
	}
	else
	{
		DissolveLineSize = float3(0, 0, 0);
	}

	float3 diffuse = (DissolveLineSize * gDissolveLineColor.rgb + albedo.rgb);
	
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