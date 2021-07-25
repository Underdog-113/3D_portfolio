matrix		g_matWorld;			// 상수 테이블
matrix		g_matView;
matrix		g_matProj;

int TilingX;
int TilingY;

float gWidth;
float gHeight;
float  gEmissionPow = 0.25f;

bool     g_zWriteEnable;

texture		g_BaseTexture;
sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;

	minfilter = linear;
	magfilter = linear;
};

texture		g_ServeTexture;
sampler ServeSampler = sampler_state
{
	texture = g_ServeTexture;

	minfilter = linear;
	magfilter = linear;
};

texture		g_DepthTexture;
sampler DepthSampler =  sampler_state
{
	texture = g_DepthTexture;
};


struct VS_IN
{
	vector		vPosition   : POSITION;		// 시만틱 : 속성 지시자
	float2		vTexUV		: TEXCOORD0;
};

struct VS_OUT
{
	vector		vPosition : POSITION;		
	float2		vTexUV : TEXCOORD0;
	vector		vProjPos : TEXCOORD1;
};

// 버텍스쉐이더

VS_OUT		VS_MAIN(VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;

	matrix			matWV, matWVP;

	matWV  = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.vPosition = mul(vector(In.vPosition.xyz, 1.f), matWVP);
	Out.vTexUV = In.vTexUV;	

	Out.vTexUV.x = Out.vTexUV.x / gWidth;
	Out.vTexUV.y = Out.vTexUV.y / gHeight;

	Out.vTexUV.x += 1 / gWidth * TilingX;
	Out.vTexUV.y += 1 / gHeight * TilingY;
	
	Out.vProjPos = Out.vPosition;

	return Out;
}


struct PS_IN
{
	float2		vTexUV : TEXCOORD0;
	vector		vProjPos : TEXCOORD1;
};

struct PS_OUT
{
	vector		vColor : COLOR0;
	vector		vEmissive : COLOR1;
};

// 픽셀 쉐이더

PS_OUT	PS_EFFECT(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;
	
	Out.vColor = tex2D(BaseSampler, In.vTexUV);		// 2차원 텍스처로부터 UV 값에 해당하는 픽셀의 색상을 추출하는 함수, 반환타입은 VECTOR 타입
	float4 alphaVal = tex2D(ServeSampler, In.vTexUV);

	Out.vColor.a = 1;
	float4 blendColor = (alphaVal * Out.vColor);

	blendColor = saturate(blendColor);
	
	Out.vColor = blendColor;
	Out.vEmissive = float4(blendColor.rgb * gEmissionPow, 1.f);

	return Out;
}

technique Default_Device
{
	pass	
	{
		CullMode = None;
		zWriteEnable = g_zWriteEnable;
		AlphaTestEnable = false;
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvsrcAlpha;
		vertexshader = compile vs_3_0 VS_MAIN();	// 진입점 함수 명시
		pixelshader = compile ps_3_0 PS_EFFECT();
	}

};