float4x4 World;
float4x4 View;
float4x4 Projection;
float4x4 WVP;
float4x4 WorldInverseTranspose;
float3 DiffuseLightDirection = float3(1, 0, 0);
float4 DiffuseColor = float4(1, 1, 1, 1);
float DiffuseIntensity = 1.0;
float4 LineColor = float4(1, 0.5, 0, 1);
float LineThickness = .03;

texture g_BaseTexture;

sampler2D BaseTexture = sampler_state
{
	Texture = (g_BaseTexture);
	MinFilter = Linear;
	MagFilter = Linear;
	AddressU = Clamp;
	AddressV = Clamp;
};

struct AppToVertex
{
	float4 Position : POSITION0; 
	float2 TextureCoordinate : TEXCOORD0; 
	float3 Normal : NORMAL0; 
};

struct VertexToPixel
{
	float4 Position : POSITION0;
	float2 TextureCoordinate : TEXCOORD0;
	float3 Normal : TEXCOORD1;
};

VertexToPixel CelVertexShader(AppToVertex input)
{
	VertexToPixel output;

	float4 worldPosition = mul(input.Position, World);
	float4 viewPosition = mul(worldPosition, View);
	output.Position = mul(viewPosition, Projection);

	output.Normal = normalize(mul(input.Normal, World));

	output.TextureCoordinate = input.TextureCoordinate;

	return output;
}

float4 CelPixelShader(VertexToPixel input) : COLOR
{
	float intensity = dot(normalize(DiffuseLightDirection), input.Normal);

if (intensity < 0)
	intensity = 0;

float4 color = tex2D(BaseTexture, input.TextureCoordinate) * DiffuseColor  * DiffuseIntensity;
color.a = 1;

//if (intensity > 0.95)
//color = float4(1.0,1,1,1.0) * color;
//else if (intensity > 0.5)
//color = float4(0.7,0.7,0.7,1.0) * color;
//else if (intensity > 0.05)
//color = float4(0.35,0.35,0.35,1.0) * color;
//else
//color = float4(0.1,0.1,0.1,1.0) * color;

color = round(intensity * 5) / 5 * color;

return color;
}

VertexToPixel OutlineVertexShader(AppToVertex input)
{
	VertexToPixel output = (VertexToPixel)0;

	float4 original = mul(mul(mul(input.Position, World), View), Projection);
	float4 normal = mul(mul(mul(input.Normal, World), View), Projection);

	output.Position = original + (mul(LineThickness, normal));

	return output;
}

float4 OutlinePixelShader(VertexToPixel input) : COLOR0
{
	return LineColor;
}


technique Toon
{
	pass Pass1
	{
		VertexShader = compile vs_2_0 OutlineVertexShader();
		PixelShader = compile ps_2_0 OutlinePixelShader();
		CullMode = CW;
	}

	pass Pass2
	{
		VertexShader = compile vs_2_0 CelVertexShader();
		PixelShader = compile ps_2_0 CelPixelShader();
		CullMode = CCW;
	}
}