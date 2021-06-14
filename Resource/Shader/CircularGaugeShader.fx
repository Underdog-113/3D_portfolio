float		g_ratio;
int			g_direction;

matrix		g_matWorld;			// 상수 테이블
matrix		g_matView;
matrix		g_matProj;

texture		g_BaseTexture;

// 샘플러 : 텍스처의 품질 및 출력 옵션을 결정하는 구조체
sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;

	minfilter = linear;
	magfilter = linear;
};

struct VS_IN
{
	vector		vPosition   : POSITION;		// 시만틱 : 속성 지시자
	float2		vTexUV		: TEXCOORD0;
};

struct VS_OUT
{
	vector		vPosition : POSITION;		
	float2 		vTexUV : TEXCOORD0;
};

// 버텍스쉐이더

VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	matrix matWV, matWVP;

	matWV  = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.vPosition = mul(vector(In.vPosition.xyz, 1.f), matWVP);

	Out.vTexUV = In.vTexUV;


	return Out;
}


struct PS_IN
{
	float2 		vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector		vColor : COLOR0;	
};

// 픽셀 쉐이더

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseSampler, In.vTexUV);


/*
	float2 d = 2.0 * In.vTexUV - float2(1.0, 1.0); // 중앙을 0,0으로 만든다음에 자신의 픽셀과 거리를 구한다.
	float r = length(d); // 백터의길이
	if (r <= 0.75) // 자신의 길이가 중심보다 0.75이상이라면 그리지않게 하기 위해서
	{
		highp float a = atan2(d.x, -d.y); // 여기부터 다시 이해해보자
		if (angleBase <= a && a <= angle) 
		{
			highp float p = (a - angleBase) / (angle - angleBase);
			gl_FragColor = vec4(0.0, 0.0, p, p) * qt_Opacity;
		}
	}
	*/

	return Out;
}

technique Default_Device
{
	pass	// 기능의 캡슐화, PASS는 이름과 상관없이 선언된 순서대로 위부터 인덱스 값이 0이 지정되고 자동적으로 하나씩 증가함
	{
		//zwriteenable = false;
		cullmode = none;

		vertexshader = compile vs_3_0 VS_MAIN();	// 진입점 함수 명시
		pixelshader = compile ps_3_0 PS_MAIN();
	}	
};