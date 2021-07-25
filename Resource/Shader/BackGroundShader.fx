matrix		g_matWorld;			// 상수 테이블
matrix		g_matView;
matrix		g_matProj;

float4		g_color;

texture		g_BaseTexture;

float		g_fPower = 0.f;

// 샘플러 : 텍스처의 품질 및 출력 옵션을 결정하는 구조체
sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;

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
};

// 픽셀 쉐이더

PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseSampler, In.vTexUV);		// 2차원 텍스처로부터 UV 값에 해당하는 픽셀의 색상을 추출하는 함수, 반환타입은 VECTOR 타입
	//Out.vColor = vector(0, 0, 0, ;
	Out.vNormal = vector(0, 0, -1, 1);

	return Out;
}


technique Default_Device
{
	pass	// 기능의 캡슐화, PASS는 이름과 상관없이 선언된 순서대로 위부터 인덱스 값이 0이 지정되고 자동적으로 하나씩 증가함
	{
		//alphablendenable = true;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		CullMode = NONE;
		vertexshader = compile vs_3_0 VS_MAIN();	// 진입점 함수 명시
		pixelshader = compile ps_3_0 PS_MAIN();
	}

	//pass	
	//{
	//	alphablendenable = true;
	//	srcblend = srcalpha;
	//	destblend = invsrcalpha;
	//
	//	vertexshader = compile vs_3_0 VS_MAIN();	// 진입점 함수 명시
	//	pixelshader = compile ps_3_0 PS_EFFECT();
	//}

};