float		g_ratio;
int			g_direction;

matrix		g_matWorld;			// ��� ���̺�
matrix		g_matView;
matrix		g_matProj;

texture		g_BaseTexture;

// ���÷� : �ؽ�ó�� ǰ�� �� ��� �ɼ��� �����ϴ� ����ü
sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;

	minfilter = linear;
	magfilter = linear;
};

struct VS_IN
{
	vector		vPosition   : POSITION;		// �ø�ƽ : �Ӽ� ������
	float2		vTexUV		: TEXCOORD0;
};

struct VS_OUT
{
	vector		vPosition : POSITION;		
	float2 		vTexUV : TEXCOORD0;
};

// ���ؽ����̴�

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

// �ȼ� ���̴�

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseSampler, In.vTexUV);

	if (g_direction == 0)
	{
		if (In.vTexUV.x >= g_ratio)
		{
			Out.vColor.a = 0;
		}
	}
	else if (g_direction == 1) 
	{
		float value = 1 - In.vTexUV.x;
		if (value >= g_ratio)
		{
			Out.vColor.a = 0;
		}
	}
	else if (g_direction == 2)
	{
		float value = 1 - In.vTexUV.y;
		if (value >= g_ratio)
		{
			Out.vColor.a = 0;
		}
	}
	else if (g_direction == 3)
	{
		if (In.vTexUV.y >= g_ratio)
		{
			Out.vColor.a = 0;
		}
	}



	return Out;
}

technique Default_Device
{
	pass	// ����� ĸ��ȭ, PASS�� �̸��� ������� ����� ������� ������ �ε��� ���� 0�� �����ǰ� �ڵ������� �ϳ��� ������
	{
		//zwriteenable = false;
		cullmode = none;

		vertexshader = compile vs_3_0 VS_MAIN();	// ������ �Լ� ����
		pixelshader = compile ps_3_0 PS_MAIN();
	}	
};