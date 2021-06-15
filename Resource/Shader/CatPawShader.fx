
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

	return(Output);

}

struct PS_INPUT
{
	float2 mUV : TEXCOORD0;
	float3 mDiffuse : TEXCOORD1;
};

float4 ps_main(PS_INPUT Input) : COLOR
{

	// ���� ����
	float intensity = dot(normalize(gWorldLightPosition), Input.mUV);


if (intensity < 0)
	intensity = 0;

	float4 albedo = tex2D(Diffuse, Input.mUV) * gDiffuseColor * gDiffuseIntensity;
	albedo.a = 1;

	float3 diffuse = saturate(Input.mDiffuse);

	diffuse = ceil(diffuse * 5) / 5.0f;
	//diffuse = round(intensity * 5) / 3 * diffuse;


	return float4(albedo * diffuse.xyz, 1);
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
	pass OutLine
	{
		VertexShader = compile vs_3_0 OutlineVertexShader();
		PixelShader = compile ps_3_0 OutlinePixelShader();
		CullMode = CW;
	}
	pass Toon
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
		CullMode = CCW;
	}

};