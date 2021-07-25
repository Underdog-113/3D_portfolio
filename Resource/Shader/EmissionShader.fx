texture g_Final;
texture g_Emissive;

texture g_EmissionBlur2;
texture g_EmissionBlur4;
texture g_EmissionBlur8;
texture g_EmissionBlur16;

static const int WINCX = 1440;
static const int WINCY = 810;
static const float perPixelX = 0.5f / WINCX;
static const float perPixelY = 0.5f / WINCY;

sampler FinalSampler = sampler_state
{
	texture = g_Final;

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;
};

sampler EmissiveSampler = sampler_state
{
	texture = g_Emissive;

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;
};

sampler EmissionBlurSampler2 = sampler_state
{
	texture = g_EmissionBlur2;

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;
};
sampler EmissionBlurSampler4 = sampler_state
{
	texture = g_EmissionBlur4;

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;

};
sampler EmissionBlurSampler8 = sampler_state
{
	texture = g_EmissionBlur8;

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;
};

sampler EmissionBlurSampler16 = sampler_state
{
	texture = g_EmissionBlur16;

	MinFilter = anisotropic;
	MagFilter = anisotropic;
	MAXANISOTROPY = 16;
};



struct VS_INPUT
{
	float3 position : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float2 uv : TEXCOORD0;

};

struct PS_INPUT
{
	float2 uv :TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 color : COLOR0;
};


VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	o.position = float4(_input.position, 1);
	o.uv = _input.uv;


	return o;
}



PS_OUTPUT PS_Main_Default(PS_INPUT  _input)
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float2 uv = float2(_input.uv) + float2(perPixelX, perPixelY);

	float3 final = tex2D(FinalSampler, uv).xyz;
	float4 emission = tex2D(EmissiveSampler, uv);

	float3 emissionBlur16 = tex2D(EmissionBlurSampler16, uv).xyz;
	float3 emissionBlur8 = tex2D(EmissionBlurSampler8, uv).xyz;
	float3 emissionBlur4 = tex2D(EmissionBlurSampler4, uv).xyz;
	float3 emissionBlur2 = tex2D(EmissionBlurSampler2, uv).xyz;
	final = final + ((emissionBlur2) * 1.3f + (emissionBlur4) * 1.5f + (emissionBlur8) * 2.5f + (emissionBlur16) * 3.5f);


	o.color = float4(final, 1);

	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();
	}
};
