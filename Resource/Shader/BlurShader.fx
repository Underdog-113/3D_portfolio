texture		g_BaseTexture;

int			g_blurSize = 3;

float		g_RTperPixelX;
float		g_RTperPixelY;

float4		g_addColor;
float4		g_color;

sampler mainSampler = sampler_state
{
	texture = g_BaseTexture;

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;

	AddressU = Mirror;
	AddressV = Mirror;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct PS_INPUT
{
	float2 uv :TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
};

float pixelKernel[13] =
{
	-6,
	-5,
	-4,
	-3,
	-2,
	-1,
	0,
	1,
	2,
	3,
	4,
	5,
	6,
};

float blurWeights[13] =
{
	0.002216,
	0.008764,
	0.026995,
	0.064759,
	0.120985,
	0.176033,
	0.199471,
	0.176033,
	0.120985,
	0.064759,
	0.026995,
	0.008764,
	0.002216,
};
// «»ºø Ω¶¿Ã¥ı

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; //

	o.pos = float4(_in.pos, 1);
	o.uv = _in.uv;

	return o;
}


PS_OUTPUT PS_Vertical(PS_INPUT IN)
{
	PS_OUTPUT Out = (PS_OUTPUT)0;

	float4 color = 0;// tex2D(mainSampler, IN.uv);

	//if (color.a == 0)
	//	return Out;
	for (int i = 0; i < 13; ++i)
	{
		//color += tex2D(mainSampler, float2(
		//	IN.uv.x + g_RTperPixelX,
		//	IN.uv.y + (pixelKernel[i] * g_RTperPixelY) + g_RTperPixelY))
		//	* blurWeights[i];
		color += tex2D(mainSampler, float2(IN.uv.x + g_RTperPixelX,
										   IN.uv.y + (pixelKernel[i] * g_RTperPixelY  * g_blurSize) + g_RTperPixelY))
				 * blurWeights[i];

	}

	Out.diffuse = color;

	return Out;
}



PS_OUTPUT PS_Horizontal(PS_INPUT  IN)
{
	PS_OUTPUT Out = (PS_OUTPUT)0;

	float4 color = 0;// tex2D(mainSampler, IN.uv);

	//if (color.a == 0)
	//	return Out;
	for (int i = 0; i < 13; ++i)
	{
		color += tex2D(mainSampler, float2(IN.uv.x + (pixelKernel[i] * g_RTperPixelX * g_blurSize) + g_RTperPixelX,
										   IN.uv.y + g_RTperPixelY))
				 * blurWeights[i];
	}

	if (color.x < 0.01f && color.y < 0.01f && color.z < 0.01f)
		color.a = 0.f;

	Out.diffuse = color;
	return Out;
}


technique DefaultTechnique
{
	Pass VerticalPass
	{
		zwriteenable = false;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Vertical();
	}

	Pass HorizontalPass
	{
		zwriteenable = false;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Horizontal();
	}
};