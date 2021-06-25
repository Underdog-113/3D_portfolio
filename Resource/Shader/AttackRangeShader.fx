float4x4 gWorldViewProjectionMatrix;
float4x4 gInvWorldMatrix;

float4x4 gWorld;
float4x4 gView;
float4x4 gProjection;

float4 gWorldLightPosition;

float  gTime;
float  gAlpha = 1.f;
float  gUVSpeed;

texture gDiffuseTex;
sampler Diffuse = sampler_state
{
	Texture = <gDiffuseTex>;
	FILTER = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

texture gAlphaTex;
sampler AlphaTex = sampler_state
{
	Texture = <gAlphaTex>;
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
	float4 vColor : COLOR0;
};


VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.mPosition = mul(Input.mPosition, gWorldViewProjectionMatrix);

	float4 objectLightPosition = mul(gWorldLightPosition, gInvWorldMatrix);
	float4 lightDir = normalize(vector(Input.mPosition.xyz, 1.f) - objectLightPosition);

	Output.mDiffuse = dot(-lightDir, normalize(Input.mNormal));
	Output.mUV = Input.mUV;/*+ float2(gTime * gUVSpeed, 0);*/

	
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
	PS_OUTPUT Out = (PS_OUTPUT)0;

	// Base albedo Texture
	float4 albedo = tex2D(Diffuse, Input.mUV);

	// Noise Texture
	float4 _Alpha = tex2D(AlphaTex, Input.mUV);

	_Alpha.a = gAlpha;

	return float4(albedo * _Alpha);
}

technique TShader
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