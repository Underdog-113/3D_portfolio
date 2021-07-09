matrix		g_matWorld;
matrix		g_matView;
matrix		g_matProj;

texture		g_BaseTexture;

float4		g_addColor;

float4		g_ambient;
float4		g_diffuse;
float4		g_emissive;
float4		g_specular;
float		g_specularPower;

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
	vector		vSpecMtrl : COLOR3;
};

// �ȼ� ���̴�

PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	float4 albedo = tex2D(BaseSampler, In.vTexUV);


	float4 diffuse = albedo * saturate(g_diffuse);
	float4 ambient = albedo * saturate(g_ambient);

	Out.vColor = ambient + diffuse;


	Out.vColor += g_addColor;


	// -1 ~ 1 -> 0 ~ 1
	// ���� ���� ������ ������ ���� ���� �ؽ��� uv ������ ���� ��ȯ
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);

	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w,	// R�� ��ġ�� z������ ���� ���� ������ z���� ����(0 ~ 1)��
		In.vProjPos.w * 0.001f,			// G�� ��ġ�� far ����� z�� ���� �佺���̽��� z���� ����(�佺���̽� ���¿��� near�� 0.1�� far�� 1000���� ������ ��Ȳ) : �츮�� �����ϰ��� �ϴ� ���´� �÷���(�÷����� ������ 0~1)
		0.f,
		0.f);


	Out.vSpecMtrl = g_specular;
	Out.vSpecMtrl.w = g_specularPower;

	Out.vColor.a = g_diffuse.x;
	Out.vNormal.a = g_diffuse.y;
	Out.vDepth.z = g_diffuse.z;
	Out.vDepth.w = g_ambient.x;

	return Out;
}

struct OUTLINE_VS_IN
{
	vector		vPosition   : POSITION;
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
};

struct OUTLINE_VS_OUT
{
	vector		vPosition	: POSITION;
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
	vector		vProjPos	: TEXCOORD1;
};


// ���ؽ����̴�
OUTLINE_VS_OUT VS_OUTLINE(OUTLINE_VS_IN In)
{
	OUTLINE_VS_OUT Out = (OUTLINE_VS_OUT)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.vPosition = mul(vector(In.vPosition.xyz, 1.f), matWVP);
	Out.vNormal = normalize(mul(vector(In.vNormal.xyz, 0.f), matWVP));
	Out.vPosition += (Out.vNormal) / 160;

	Out.vTexUV = In.vTexUV;

	Out.vProjPos = Out.vPosition;

	return Out;
}

struct OUTLINE_PS_IN
{
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
	vector		vProjPos	: TEXCOORD1;
};

struct OUTLINE_PS_OUT
{
	vector		vColor : COLOR0;
	vector		vNormal : COLOR1;
	vector		vDepth : COLOR2;
	vector		vSpecMtrl : COLOR3;
};

OUTLINE_PS_OUT PS_OUTLINE(OUTLINE_PS_IN In)
{
	OUTLINE_PS_OUT Out = (OUTLINE_PS_OUT)0;

	Out.vColor = float4(0, 0, 0, 1);
	Out.vNormal = float4(0, 0, 0, 1);
	Out.vDepth = float4(0, 0, 0, 1);
	Out.vSpecMtrl = float4(0, 0, 0, 1);

	return Out;
}

technique Default_Device
{
	pass Outline
	{
		vertexshader = compile vs_3_0 VS_OUTLINE();
		pixelshader = compile ps_3_0 PS_OUTLINE();
		CullMode = CW;
	}

	pass Origin
	{
		vertexshader = compile vs_3_0 VS_MAIN();
		pixelshader = compile ps_3_0 PS_MAIN();
		CullMode = CCW;
	}
};