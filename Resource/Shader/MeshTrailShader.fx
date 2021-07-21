float4x4 gWorldViewProjectionMatrix;
float4x4 gInvWorldMatrix;

float4x4 gWorld;
float4x4 gView;
float4x4 gProjection;

float4 gWorldLightPosition;

float  gTime;
float  gTrailAlpha;
bool   gisSpawn;

float  m_defaultDissolveVal = 0.9f;

texture g_DiffuseTex;
sampler Diffuse = sampler_state
{
	Texture = <g_DiffuseTex>;
	FILTER = MIN_MAG_MIP_LINEAR;
};

texture g_ServeTex;
sampler ServeTex = sampler_state
{
	Texture = <g_ServeTex>;
	FILTER = MIN_MAG_MIP_LINEAR;
};

texture g_AlphaTex;
sampler AlphaTex = sampler_state
{
	Texture = <g_AlphaTex>;
	FILTER = MIN_MAG_MIP_LINEAR;
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
	float4 lightDir = normalize(Input.mPosition - objectLightPosition);

	Output.mDiffuse = dot(-lightDir.xyz, normalize(Input.mNormal));
	Output.mUV = Input.mUV;

	return(Output);

}

struct PS_INPUT
{
	float2 mUV : TEXCOORD0;
	float3 mDiffuse : TEXCOORD1;
	float3 mNormal	 : NORMAL;
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

	// Noise Texture
	float4 Serve = tex2D(ServeTex, Input.mUV);

	// Alpha Texture
	float4 Alpha = tex2D(AlphaTex, Input.mUV);

	float4 blendColor = (Alpha * albedo) + ((1.f - Alpha) * Serve);
	
	blendColor.a = 0;
	blendColor = saturate(blendColor);	

	if (Input.mUV.x > gTrailAlpha)
	{
		float multiply1 = saturate((Alpha.r * sin(gTrailAlpha)) * 5.5f);
		float multiply2 = saturate(Alpha.r * sin(gTrailAlpha));

		float CurrentDissolveVal = saturate(pow(multiply1 + multiply2, 25));

		float multiple = pow(multiply1 + multiply2, 25);

		// Dissolve Line Size
		float3 DissolveLineSize;
		float3 DissolveLineColor = blendColor.rgb;

		if (m_defaultDissolveVal >= CurrentDissolveVal)
		{
			DissolveLineSize = float3(1.f, 0.f, 0.f);
		}
		else
		{
			DissolveLineSize = float3(0, 0, 0);
		}

		float3 diffuse = (DissolveLineSize * DissolveLineColor + blendColor.rgb);
			
		Out.vColor = float4(diffuse, multiple);

		if (Out.vColor.r == 1 && Out.vColor.g == 1  && Out.vColor.b == 1)
		{
			Out.vColor = float4(0.f,0.f,0.f,0.f);
		}
		else
		{
			Out.vColor = float4(diffuse, multiple);
			Out.vEmissive = float4(Out.vColor.rgb, gTrailAlpha - 0.1f);
		}


		return Out;
	}		
	return Out;
}

technique TrailShader
{
	pass p0
	{
		CullMode = None;
		AlphaBlendEnable = true;
		AlphaTestEnable = false;
		zWriteEnable = true;
		DestBlend = InvsrcAlpha;
		SrcBlend = SrcAlpha;

		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}

};