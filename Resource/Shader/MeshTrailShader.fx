float4x4 gWorldViewProjectionMatrix;
float4x4 gInvWorldMatrix;

float4x4 gWorld;
float4x4 gView;
float4x4 gProjection;

float4 gWorldLightPosition;

float  gTime;
float  gTrailAlpha;
bool   gisSpawn;

texture g_DiffuseTex;
sampler Diffuse = sampler_state
{
	Texture = <g_DiffuseTex>;
	FILTER = MIN_MAG_MIP_LINEAR;
};

texture g_NoiseTex;
sampler NoiseTex = sampler_state
{
	Texture = <g_NoiseTex>;
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

struct PS_OUTPUT
{
	float4 mHSBC   : COLOR;
	float4 vColor  : COLOR0;
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

float3 applyHue(float3 aColor, float aHue)
{
	float angle = radians(aHue);
	float3 k = float3(0.57735, 0.57735, 0.57735);
	float cosAngle = cos(angle);

	//Rodrigues' rotation formula
	return aColor * cosAngle + cross(k, aColor) * sin(angle) + k * dot(k, aColor) * (1 - cosAngle);
}



float4 ps_main(VS_OUTPUT Input) : COLOR
{
	PS_OUTPUT Out = (PS_OUTPUT)0;

	Out.mHSBC = float4(1,1,1,1);

	float _Hue = 360 * Out.mHSBC.r;
    float _Brightness = Out.mHSBC.g * 2 - 1;
    float _Contrast = Out.mHSBC.b * 2;
    float _Saturation = Out.mHSBC.a * 2;

	// Base albedo Texture
	float4 albedo = tex2D(Diffuse, Input.mUV);

	float4 outputColor = albedo;

	outputColor.rgb = applyHue(outputColor.rgb, _Hue);
	outputColor.rgb = (outputColor.rgb - 0.5f) * (_Contrast)+0.5f;
	outputColor.rgb = outputColor.rgb + _Brightness;

	float3 intensity = dot(outputColor.rgb, float3(0.299, 0.587, 0.114));
	outputColor.rgb = lerp(intensity, outputColor.rgb, _Saturation);

	// Noise Texture
	float4 Noise = tex2D(NoiseTex, Input.mUV);
	
	if (Input.mUV.x > gTrailAlpha)
	{
		outputColor.a = 0;
		Noise.a = 0;
	}	

	return outputColor * Noise;
}

float4 ps_alpha(VS_OUTPUT Input) : COLOR
{
	PS_OUTPUT Out = (PS_OUTPUT)0;

    Out.vColor = tex2D(Diffuse, Input.mUV);
    
	if (Input.mUV.x > gTrailAlpha)
	{
		Out.vColor.a = 0;
	}

	return Out.vColor;
}


technique ToonShader
{
	pass p0
	{
		AlphaBlendEnable = true;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}

	pass p1
	{
		AlphaBlendEnable = true;		
		alphafunc = greater;
		alpharef = 0xc0;
		CullMode = none;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_alpha();
	}

};