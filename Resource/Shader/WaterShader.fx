matrix g_WorldMat;
matrix g_ViewMat;
matrix g_ProjMat;

float4 g_WorldLightPos;
float4 g_WorldCameraPos;

float g_fTime;
float g_UVSpeed = 0.1;

float g_WaveHeight = 0.5;
float g_WaveFrequency = 30;
float g_Speed = 0.5;
float3 g_LightColor;

texture g_DiffuseTex;
sampler Diffuse = sampler_state
{
	Texture = <g_DiffuseTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
};

texture g_NoiseTex;
sampler NoiseTex = sampler_state
{
	Texture = <g_NoiseTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
};

struct VS_INPUT
{
	float4 mPosition   : POSITION;
	float3 mNormal     : NORMAL;
	float2 mUV		   : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 mPosition   : POSITION;
	float2 mUV		   : TEXCOORD0;
	float3 mDiffuse    : TEXCOORD1;
	float3 mViewDir    : TEXCOORD2;
	float3 mReflection : TEXCOORD3;
	vector vProjPos	   : TEXCOORD4;
};

VS_OUTPUT VS_MAIN(VS_INPUT Input)
{
	VS_OUTPUT Out;

	float cosTime = g_WaveHeight * cos(g_fTime * g_Speed + Input.mUV.x * g_WaveFrequency);

	Input.mPosition.y += cosTime;

	Out.mPosition = mul(Input.mPosition, g_WorldMat);

	float3 lightDir = Out.mPosition.xyz - g_WorldLightPos.xyz;
	lightDir = normalize(lightDir);

	float3 viewDir = normalize(Out.mPosition.xyz - g_WorldCameraPos.xyz);
	Out.mViewDir = viewDir;

	Out.mPosition = mul(Out.mPosition, g_ViewMat);
	Out.mPosition = mul(Out.mPosition, g_ProjMat);

	float3 worldNormal = mul(Input.mNormal, (float3x3)g_WorldMat);
	worldNormal = normalize(worldNormal);

	Out.mDiffuse = dot(-lightDir, worldNormal);
	Out.mReflection = reflect(lightDir, worldNormal);
	Out.mUV = Input.mUV/* + float2(g_fTime * g_UVSpeed, g_fTime * 0.005)*/;
	Out.vProjPos = Out.mPosition;

	return Out;
}

struct PS_INPUT
{
	float2 mUV : TEXCOORD0;
	float3 mDiffuse : TEXCOORD1;
	float3 mViewDir : TEXCOORD2;
	float3 mReflection : TEXCOORD3;
	vector vProjPos	   : TEXCOORD4;
};

struct PS_OUTPUT
{
	vector		vColor : COLOR0;
	vector		vNormal : COLOR1;
	vector		vDepth : COLOR2;
	//vector		vEmissive : COLOR3;
};

PS_OUTPUT PS_MAIN(PS_INPUT Input)
{
	PS_OUTPUT Out = (PS_OUTPUT)0;

	float4 albedo = tex2D(Diffuse, (Input.mUV * 50) + float2(g_fTime * g_UVSpeed, 0.f));
	float4 Noise = tex2D(NoiseTex, (Input.mUV * 50) * albedo.r - float2(g_fTime * g_UVSpeed, 0.f));

	Out.vColor = saturate(albedo * Noise);
	Out.vColor.xyz *= 0.7f;
	Out.vNormal = float4(0, 1, 0, 0);
	Out.vDepth = vector(Input.vProjPos.z / Input.vProjPos.w,	// R에 위치에 z나누기 끝난 투영 공간의 z값을 보관(0 ~ 1)값
						Input.vProjPos.w * 0.001f,			// G에 위치에 far 평면의 z로 나눈 뷰스페이스의 z값을 보관(뷰스페이스 상태에서 near는 0.1로 far는 1000으로 설정한 상황) : 우리가 보관하고자 하는 형태는 컬러값(컬러값의 범위는 0~1)
						0.f,
						0.f);
	//Out.vEmissive = float4(0, 0, 0, 1);	

	return Out;
}


technique TShader
{
	pass UVAnim
	{
		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
		CullMode = CCW;
	}
};
