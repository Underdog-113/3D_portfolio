float4x4 gWorldViewProjectionMatrix;
float4x4 gInvWorldMatrix;

float4x4 gWorld;
float4x4 gView;
float4x4 gProjection;

float4 gWorldLightPosition;

float  gTime;
float  gAlpha;
float  m_defaultDissolveVal = 0.9f;

float4		g_addColor;
float4		g_multColor;
float4		g_color;


float4 gDissolveLineColor = float4(1,1,1,1);

bool   gTrailCheck;
bool   g_zWriteEnabled;

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


texture g_ServeTex;
sampler ServeTex = sampler_state
{
	Texture = <g_ServeTex>;
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
	vector mProjPos	: TEXCOORD2;


};

struct PS_OUT
{
	vector		vColor : COLOR0;
	vector		vNormal : COLOR1;
	vector		vDepth : COLOR2;
	vector      vEmissive : COLOR3;
};

PS_OUT ps_main(VS_OUTPUT Input)
{
	PS_OUT		Out = (PS_OUT)0;

	// Base albedo Texture
	float4 albedo = float4(0,0,0,1);

	// Serve Texture
	float4 Serve = tex2D(ServeTex, Input.mUV);

	// Noise Texture
	float4 Noise = tex2D(NoiseTex, Input.mUV);

	float4 blendColor = (Noise * albedo) + ((1.0f - Noise) * albedo);

	blendColor.a = 0;
	blendColor = saturate(blendColor);

	// To disappear to match the noise texture
	float multiply1 = 0;
	float multiply2 = 0;

	multiply1 = saturate((Noise.r * sin(gAlpha)) * 5.5);
	multiply2 = saturate(Noise.r * sin(gAlpha));

	// Current Dissolve Line Value
	float CurrentDissolveVal = saturate(pow(multiply1 + multiply2, 20));

	// Returns the "multiply2" multiple of "multiply1"
	float multiple = 0;

	multiple = pow(multiply1 + multiply2, 20);

	// Dissolve Line Size
	float3 DissolveLineSize;

	if (m_defaultDissolveVal >= CurrentDissolveVal)
	{
		DissolveLineSize = float3(0.f, 0.f, 1.f);
	}
	else
	{
		DissolveLineSize = float3(0, 0, 0);
	}

	float3 diffuse = float3(0, 0, 0);

	diffuse = (DissolveLineSize * gDissolveLineColor.rgb + blendColor.rgb);
	Out.vColor = float4(diffuse.rgb, multiple);

	if (Out.vColor.b > 0.99f)
	{
		Out.vEmissive = float4(float3(0, 0, 1) * 0.05f, 1.f);
	}

	return Out;
}

PS_OUT		ps_serve(PS_INPUT In)
{
	PS_OUT		Out = (PS_OUT)0;

	float4 Serve = tex2D(ServeTex, In.mUV);

	Out.vColor = Serve;
	Out.vColor.a = 1.f;


	Out.vColor += g_addColor;
	Out.vColor *= g_multColor;
	Out.vColor = Out.vColor * g_color;

	// -1 ~ 1 -> 0 ~ 1
	// 단위 벡터 상태인 월드의 법선 값을 텍스쳐 uv 값으로 강제 변환


	Out.vNormal = vector(In.mNormal.xyz * 0.5f + 0.5f, 1.f);

	Out.vDepth = vector(In.mProjPos.z / In.mProjPos.w,	// R에 위치에 z나누기 끝난 투영 공간의 z값을 보관(0 ~ 1)값
		In.mProjPos.w * 0.001f,			// G에 위치에 far 평면의 z로 나눈 뷰스페이스의 z값을 보관(뷰스페이스 상태에서 near는 0.1로 far는 1000으로 설정한 상황) : 우리가 보관하고자 하는 형태는 컬러값(컬러값의 범위는 0~1)
		0.f,
		0.f);

	if (Out.vColor.b > 0.99f)
	{
		Out.vEmissive = float4(float3(0,0,1) * 0.05f, 1.f ) ;
	}

	return Out;
}


technique DissolveShader
{
	pass p0
	{
		CullMode = CCW;
		AlphaBlendEnable = true;
		DestBlend = InvsrcAlpha;
		SrcBlend = SrcAlpha;
		alphafunc = greater;
		alpharef = 0x08;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_serve();
	}

	pass p1
	{
		CullMode = CCW;
		AlphaBlendEnable = true;
		DestBlend = InvsrcAlpha;
		SrcBlend = SrcAlpha;
		alphafunc = greater;
		alpharef = 0x08;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}
};