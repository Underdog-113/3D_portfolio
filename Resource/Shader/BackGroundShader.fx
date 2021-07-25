matrix		g_matWorld;			// ��� ���̺�
matrix		g_matView;
matrix		g_matProj;

float4		g_color;

texture		g_BaseTexture;

float		g_fPower = 0.f;

// ���÷� : �ؽ�ó�� ǰ�� �� ��� �ɼ��� �����ϴ� ����ü
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
	vector		vPosition   : POSITION;		// �ø�ƽ : �Ӽ� ������
	float2		vTexUV		: TEXCOORD0;
};

struct VS_OUT
{
	vector		vPosition : POSITION;		
	float2		vTexUV : TEXCOORD0;
	vector		vProjPos : TEXCOORD1;
};

// ���ؽ����̴�

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

// �ȼ� ���̴�

PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseSampler, In.vTexUV);		// 2���� �ؽ�ó�κ��� UV ���� �ش��ϴ� �ȼ��� ������ �����ϴ� �Լ�, ��ȯŸ���� VECTOR Ÿ��
	//Out.vColor = vector(0, 0, 0, ;
	Out.vNormal = vector(0, 0, -1, 1);

	return Out;
}


technique Default_Device
{
	pass	// ����� ĸ��ȭ, PASS�� �̸��� ������� ����� ������� ������ �ε��� ���� 0�� �����ǰ� �ڵ������� �ϳ��� ������
	{
		//alphablendenable = true;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		CullMode = NONE;
		vertexshader = compile vs_3_0 VS_MAIN();	// ������ �Լ� ���
		pixelshader = compile ps_3_0 PS_MAIN();
	}

	//pass	
	//{
	//	alphablendenable = true;
	//	srcblend = srcalpha;
	//	destblend = invsrcalpha;
	//
	//	vertexshader = compile vs_3_0 VS_MAIN();	// ������ �Լ� ���
	//	pixelshader = compile ps_3_0 PS_EFFECT();
	//}

};