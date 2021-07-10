matrix		g_matWorld;
matrix		g_matView;
matrix		g_matProj;

float4		g_faceDir;

texture		g_BaseTexture;

bool g_timeSlow;

sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;

	minfilter = linear;
	magfilter = linear;
};

struct VS_IN
{
	vector		vPosition   : POSITION;
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
};

struct VS_OUT
{
	vector		vPosition	: POSITION;
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
	vector		vProjPos	: TEXCOORD1;
};

// ���ؽ����̴�
VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.vPosition = mul(vector(In.vPosition.xyz, 1.f), matWVP);
	Out.vNormal = normalize(mul(vector(In.vNormal.xyz, 0.f), g_matWorld));

	Out.vTexUV = In.vTexUV;

	Out.vProjPos = Out.vPosition;

	return Out;
}


struct PS_IN
{
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
	vector		vProjPos	: TEXCOORD1;
};

struct PS_OUT
{
	vector		vColor : COLOR0;
	vector		vNormal : COLOR1;
	vector		vDepth : COLOR2;
};

// �ȼ� ���̴�

PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	float4 albedo = tex2D(BaseSampler, In.vTexUV);

	Out.vColor = albedo;
	Out.vColor.a = 1;

	// -1 ~ 1 -> 0 ~ 1
	// ���� ���� ������ ������ ���� ���� �ؽ��� uv ������ ���� ��ȯ
	Out.vNormal = g_faceDir;
	Out.vNormal.a = 0;

	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w,	// R�� ��ġ�� z������ ���� ���� ������ z���� ����(0 ~ 1)��
		In.vProjPos.w * 0.001f,			// G�� ��ġ�� far ������ z�� ���� �佺���̽��� z���� ����(�佺���̽� ���¿��� near�� 0.1�� far�� 1000���� ������ ��Ȳ) : �츮�� �����ϰ��� �ϴ� ���´� �÷���(�÷����� ������ 0~1)
		0.f,
		0.f);

	return Out;
}

technique Default_Device
{
	pass Origin
	{
		vertexshader = compile vs_3_0 VS_MAIN();
		pixelshader = compile ps_3_0 PS_MAIN();
		CullMode = CCW;
	}
};
