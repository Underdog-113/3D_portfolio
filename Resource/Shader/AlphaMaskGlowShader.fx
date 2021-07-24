float4x4 gWorldViewProjectionMatrix;
float4x4 gInvWorldMatrix;

float4x4 gWorld;
float4x4 gView;
float4x4 gProjection;

float4 gWorldLightPosition;

float  gAlpha;
float  gSpeed;
float  gTmpAlpha;
float  g_fGlow = 0.2;

bool   gPlayingAnim;
bool   gPlayingAnim_UpDown = false;
bool   g_bAlphaCtrl;
bool   g_zWriteEnabled = false;
bool   g_AlphaTestEnabled = false;

texture g_DiffuseTex;
sampler Diffuse = sampler_state
{
	Texture = <g_DiffuseTex>;
	FILTER = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

texture g_ServeTex;
sampler ServeTex = sampler_state
{
	Texture = <g_ServeTex>;
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

	if (gPlayingAnim_UpDown)
	{
		Output.mUV = Input.mUV + float2(0.f, gSpeed);
	}
	else if (gPlayingAnim)
	{
		Output.mUV = Input.mUV + float2(gSpeed, 0.f);
	}
	else
	{
		Output.mUV = Input.mUV;
	}

	return Output;

}

struct PS_INPUT
{
	float2 mUV : TEXCOORD0;
};

struct PS_OUTPUT
{
	vector		vColor : COLOR0;
	vector		vNormal : COLOR1;
	vector		vDepth	: COLOR2;
	vector		vEmissive : COLOR3;
};

PS_OUTPUT ps_main(VS_OUTPUT Input)
{
	PS_OUTPUT Out = (PS_OUTPUT)0;

	// Base albedo Texture
	float4 albedo = tex2D(Diffuse, Input.mUV);	
	float4 alphaVal = tex2D(ServeTex, Input.mUV);
	
	if (g_bAlphaCtrl)
	{
		if (Input.mUV.x >= gAlpha)
		{
			albedo.a = 0;
		}
		alphaVal.a = gTmpAlpha;
	}
	else
		albedo.a = gAlpha;

	float4 blendColor = (alphaVal * albedo);	

	blendColor = saturate(blendColor);

	Out.vColor = blendColor;
	Out.vEmissive = float4(blendColor.rgb, gAlpha - g_fGlow);

	return Out;
}

technique AlphaMask
{
	pass p0
	{
		CullMode = None;
		zWriteEnable = g_zWriteEnabled;
		AlphaTestEnable = g_AlphaTestEnabled;
		AlphaBlendEnable = true;
		DestBlend = InvsrcAlpha;
		SrcBlend = SrcAlpha;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}
};