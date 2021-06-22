
float4x4 gWorldViewProjectionMatrix;
float4x4 gInvWorldMatrix;

float4x4 gWorld;
float4x4 gView;
float4x4 gProjection;

float4 gWorldLightPosition;
float3 gSurfaceColor;

float4 gDiffuseColor = float4(1, 1, 1, 1);
float  gDiffuseIntensity = 1.0;
float4 gLineColor = float4(1, 0.5, 0, 1);
float  gLineThickness = .01;

float3 gViewDir = float3(1, 1, 0);
float4 gRimColor = float4(1, 1, 0, 1);
float  gRimPower = 3.f;

texture g_DiffuseTex;
sampler Diffuse = sampler_state
{
	Texture = <g_DiffuseTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Clamp;
	AddressV = Clamp;
};

texture g_Face;
sampler Face = sampler_state
{
	Texture = <g_Face>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Clamp;
	AddressV = Clamp;
};

texture g_Body;
sampler Body = sampler_state
{
	Texture = <g_Body>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Clamp;
	AddressV = Clamp;
};

texture g_Hair;
sampler Hair = sampler_state
{
	Texture = <g_Hair>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Clamp;
	AddressV = Clamp;
};

texture g_Hair2;
sampler Hair2 = sampler_state
{
	Texture = <g_Hair2>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Clamp;
	AddressV = Clamp;
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

	float3 objectLightPosition = mul(gWorldLightPosition, gInvWorldMatrix);
	float3 lightDir = normalize(Input.mPosition.xyz - objectLightPosition);

	Output.mDiffuse = dot(-lightDir, normalize(Input.mNormal));
	Output.mUV = Input.mUV;

	return (Output);

}

struct PS_INPUT
{
	float2 mUV : TEXCOORD0;
	float3 mDiffuse : TEXCOORD1;
	float3 mNormal	 : NORMAL;

};

float4 ps_main(PS_INPUT Input) : COLOR
{
	// ºûÀÇ °­µµ
	float intensity = dot(normalize(gWorldLightPosition), Input.mUV);

	if (intensity < 0)
		intensity = 0;

	float4 albedo = tex2D(Diffuse, Input.mUV) * gDiffuseColor * gDiffuseIntensity;
	albedo.a = 1;

	float4 mFace = tex2D(Face, Input.mUV);
	float4 mBody = tex2D(Body, Input.mUV);
	float4 mHair = tex2D(Hair, Input.mUV);
	float4 mHair2 = tex2D(Hair2, Input.mUV);

	float3 diffuse = saturate(Input.mDiffuse);

	diffuse = ceil(diffuse * intensity * 5) / 5.0f;

	float rim = saturate(abs(dot(Input.mNormal, gViewDir)));
	float3 Emission = pow(1 - rim, gRimPower) * gRimColor.rgb;

	return float4(albedo * diffuse.xyz * mFace * mBody * mHair * mHair2, 1) ;
}

VS_OUTPUT OutlineVertexShader(VS_INPUT Input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float4 original = mul(mul(mul(Input.mPosition, gWorld), gView), gProjection);
	float4 normal = mul(mul(mul(Input.mNormal, gWorld), gView), gProjection);

	output.mPosition = original + (mul(gLineThickness, normal));

	return output;
}

float4 OutlinePixelShader(VS_OUTPUT Input) : COLOR0
{
	return gLineColor;
}


technique ToonShader
{
	/* pass OutLine
	{
		VertexShader = compile vs_3_0 OutlineVertexShader();
		PixelShader = compile ps_3_0 OutlinePixelShader();
		CullMode = CW;
	} */
		pass Toon
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
		//CullMode = CCW;
	}
};