matrix		g_matWorld;			// 상수 테이블
matrix		g_matView;
matrix		g_matProj;

int TilingX;
int TilingY;

float gWidth;
float gHeight;

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
	vector		vNormal : COLOR1;
	vector		vDepth	: COLOR2;
	vector		vEmissive : COLOR3;
};

// 픽셀 쉐이더

PS_OUT	PS_EFFECT(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;
	
	Out.vColor = tex2D(BaseSampler, In.vTexUV);		// 2차원 텍스처로부터 UV 값에 해당하는 픽셀의 색상을 추출하는 함수, 반환타입은 VECTOR 타입
	float4 alphaVal = tex2D(ServeSampler, In.vTexUV);

	//float2		vDetphUV = (float2)0.f;

	//// z나누기가 끝난 투영 영역의 x값(-1~1)을 텍스처 u값(0~1)으로 변환
	//vDetphUV.x = (In.#vProjPos.x / In.vProjPos.w) * 0.5f + 0.5f;
	////// z나누기가 끝난 투영 영역의 y값(1~-1)을 텍스처 u값(0~1)으로 변환
	//vDetphUV.y = (In.vProjPos.y / In.vProjPos.w) * -0.5f + 0.5f;

	//// 텍스처 내의 픽셀의 뷰스페이스 상의 z를 추출
	//float fViewZ = tex2D(DepthSampler, vDetphUV).y * 1000.f;

	//Out.vColor.a = Out.vColor.a * max((fViewZ - In.vProjPos.w), 0.f);

	Out.vColor.a = 1;
	float4 blendColor = (alphaVal * Out.vColor);

	blendColor = saturate(blendColor);
	
	Out.vColor = blendColor;

	if (Out.vColor.a != 0)
		Out.vEmissive = blendColor;

	return Out;
}

technique Default_Device
{
	pass	
	{
		CullMode = None;
		AlphaTestEnable = true;
		zWriteEnable = g_zWriteEnable;
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvsrcAlpha;
		vertexshader = compile vs_3_0 VS_MAIN();	// 진입점 함수 명시
		pixelshader = compile ps_3_0 PS_EFFECT();
	}

};