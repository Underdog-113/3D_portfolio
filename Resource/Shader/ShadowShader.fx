matrix		g_matWorld;
matrix		g_matView;
matrix		g_matProj;
matrix		g_matLightView;
matrix		g_matLightProj;

texture		g_BaseTexture;
texture		g_DepthTexture;



vector		g_vLightDir;
vector		g_vLightPos;


sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;
	AddressU = Clamp;
	AddressV = Clamp;
};

sampler DepthSampler = sampler_state
{
	texture = g_DepthTexture;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_IN
{
	vector		vPosition   : POSITION;
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
};

struct PS_IN
{
	vector		vPosition		: POSITION;
	float2		vTexUV			: TEXCOORD0;
	vector		vNormal			: NORMAL;
	vector		vLightViewPos	: TEXCOORD1;
};

struct PS_OUT
{
	vector vShadow	: COLOR0;
};

PS_IN VS_MAIN(VS_IN In)
{
	PS_IN Out = (PS_IN)0;

	float4 worldPos;

	matrix matWV, matWVP;
	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	worldPos		= mul(vector(In.vPosition.xyz, 1.f), g_matWorld);
	Out.vPosition	= mul(vector(In.vPosition.xyz, 1.f), matWVP);
	Out.vTexUV		= In.vTexUV;
	Out.vNormal		= normalize(mul(vector(In.vNormal.xyz, 0.f), g_matWorld));

	matrix matLightWV, matLightWVP;
	matLightWV = mul(g_matWorld, g_matLightView);
	matLightWVP = mul(matLightWV, g_matLightProj);

	Out.vLightViewPos = mul(vector(In.vPosition.xyz, 1.f), matLightWVP);


	return Out;
} 


PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;
	Out.vShadow = (vector)0.2f;

	float bias;
	float2 projTexCoord;
	float depthValue;
	float lightDepthValue;
	float lightIntensity;
	float3 lightDir;
	float4 textureColor;
	
	lightDir = -g_vLightDir.xyz;
	
	bias = 0.001f;
	projTexCoord.x = (In.vLightViewPos.x / In.vLightViewPos.w) * 0.5f + 0.5f;
	projTexCoord.y = (In.vLightViewPos.y / In.vLightViewPos.w) * 0.5f + 0.5f;

	if ((saturate(projTexCoord.x) == projTexCoord.x) && (saturate(projTexCoord.y) == projTexCoord.y))
	{
		depthValue = tex2D(DepthSampler, projTexCoord).r;
		lightDepthValue = (In.vLightViewPos.z / In.vLightViewPos.w) - bias;

		if(lightDepthValue < depthValue)
		{
			lightIntensity = saturate(dot(In.vNormal, lightDir));
			if (lightIntensity > 0.f)
			{
				Out.vShadow += saturate((vector)lightIntensity);
			}
		}
	}
	else
	{
		lightIntensity = saturate(dot(In.vNormal, lightDir));
		if (lightIntensity > 0.f)
		{
			Out.vShadow += saturate((vector)lightIntensity);
		}
	}
	textureColor = tex2D(BaseSampler, In.vTexUV);
	Out.vShadow = Out.vShadow * textureColor;
	return Out;
}


technique Default_Device
{
	pass Shadow
	{
		vertexshader = compile vs_3_0 VS_MAIN();
		pixelshader = compile ps_3_0 PS_MAIN();
		CullMode = CCW;
	}
};