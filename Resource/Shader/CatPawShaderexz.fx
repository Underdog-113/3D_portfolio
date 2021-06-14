
matrix g_WorldMat;
matrix g_ViewMat;
matrix g_ProjMat;

matrix g_WVP;

float3 g_WorldCameraPos;

float3 g_LightColor;
float4 g_RimColor;
float  g_RimPower;

float4 g_ViewPosition;
float4 g_ViewProjection;
float4 g_LineColor;

texture g_DiffuseTex;
sampler Diffuse = sampler_state
{
	Texture = <g_DiffuseTex>;
	//MinFilter = LINEAR;
	//MagFilter = LINEAR;
	//MipFilter = NONE;
};

texture g_BumpMap;
sampler BumpMap = sampler_state
{
	Texture = <g_BumpMap>;
	/*MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;*/
};


struct VS_INPUT
{
	float4 mPosition   : POSITION0;
	float3 mNormal     : NORMAL0;
	float2 mUV		   : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 mPosition   : POSITION0;
	float4 mColor : COLOR0;
	float2 mUV		   : TEXCOORD0;
	float3 mDirection  : TEXCOORD1;
	float3 mNormal     : NORMAL;
};

float fLineWidth = 3.f;

VS_OUTPUT VS_MAIN(VS_INPUT Input)
{
	VS_OUTPUT Out;

	float4 ViewPos = g_ViewPosition;
	ViewPos = mul(g_WorldMat, g_ViewPosition);
	Input.mPosition = mul(g_WorldMat, Input.mPosition);
	Input.mNormal = normalize(mul((float3x3)g_WorldMat, Input.mNormal));
	Input.mNormal *= fLineWidth * 0.3f;
	Input.mPosition += float4(Input.mNormal, 0);

	Out.mPosition = mul(g_ViewProjection, Input.mPosition);
	Out.mColor = g_LineColor;


	//Out.mPosition = Input.mPosition;/* mul(Input.mPosition, g_WVP);*/
	Out.mUV = Input.mUV;
	Out.mNormal = normalize(Input.mNormal);

	Out.mDirection = normalize(g_WorldCameraPos - Input.mPosition);

	return Out;
}

struct PS_INPUT
{
	float2 mUV : TEXCOORD0;
	float3 mDiffuse : TEXCOORD2;
	float3 mViewDir : TEXCOORD3;
	float3 mNormal     : NORMAL;
	float3 mDirection   : TEXCOORD4;
};

// 외곽선 검출

float3x3 Kx = { -1, 0, 1,
-2, 0, 2,
-1, 0, 1 };

float3x3 Ky = { 1, 2, 1,
0, 0, 0,
-1, -2, -1 };

float g_PixelOffsetX;
float g_PixelOffsetY;


float4 PS_MAIN(PS_INPUT Input) : COLOR
{
	float Lx = 0;
float Ly = 0;
//float4 albedoTex = tex2D(Diffuse, Input.mUV);

for (int y = -1; y <= 1; ++y)
{
	for (int x = -1; x <= 1; ++x)
	{
		float2 offset = float2(x, y) * float2(g_PixelOffsetX, g_PixelOffsetY);
		float3 albedo = tex2D(Diffuse, Input.mUV + offset).rgb;
		float luminance = dot(albedo, float3(0.3, 0.59, 0.11));

		Lx += luminance * Kx[y + 1][x + 1];
		Ly += luminance * Ky[y + 1][x + 1];

	}
}

float L = sqrt((Lx * Lx) + (Ly * Ly));

// 림라이트
float rim = 1.0f - saturate(abs(dot(Input.mNormal, Input.mDirection)));

float4 rc = g_RimColor * 1.f;

return float4(/*albedoTex + pow(rim, g_RimPower) + */L.xxx /*+ pow(rim, g_RimPower)*/, 1) * rc;
//return float4(albedo + pow(rim, g_RimPower)) * rc;
}


technique TShader
{

	pass UVAnim
	{
		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
};
