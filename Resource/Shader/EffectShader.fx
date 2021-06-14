matrix g_WorldMat;
matrix g_ViewMat;
matrix g_ProjMat;

float4 g_WorldLightPos;
float4 g_WorldCameraPos;

float g_fTime;
float g_fUVSpeed;

texture g_DiffuseTex;
sampler Diffuse = sampler_state
{
	Texture = <g_DiffuseTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
};

texture g_SpecularTex;
sampler Specular = sampler_state
{
	Texture = <g_SpecularTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
};
float3 g_LightColor;

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
};

VS_OUTPUT VS_MAIN(VS_INPUT Input)
{
	VS_OUTPUT Out;

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
	Out.mUV = Input.mUV + float2(g_fTime * g_fUVSpeed, g_fTime * g_fUVSpeed);

	return Out;
}

struct PS_INPUT
{
	float2 mUV : TEXCOORD0;
	float3 mDiffuse : TEXCOORD1;
	float3 mViewDir : TEXCOORD2;
	float3 mReflection : TEXCOORD3;
};



float4 PS_MAIN(PS_INPUT Input) : COLOR
{
	float4 albedo = tex2D(Diffuse, Input.mUV);
	float3 diffuse = g_LightColor * albedo.rgb * saturate(Input.mDiffuse);

	float3 reflection = normalize(Input.mReflection);
	float3 viewDir = normalize(Input.mViewDir);
	float3 specular = 0;

	if (diffuse.x > 0)
	{
		specular = saturate(dot(reflection, -viewDir));
		specular = pow(specular, 20.f);

		float4 specularIntensity = tex2D(Specular, Input.mUV);
		specular *= specularIntensity.rgb * g_LightColor;
	}

	float3 ambient = float3(0.1f, 0.1f, 0.1f) * albedo;

	return float4(ambient + diffuse + specular, 1);
}


technique TShader
{
	pass UVAnim
	{
		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
};