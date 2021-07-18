float4x4 mWVP;
float4x4 mWV;
float gFar;

texture      g_BaseTexture;

matrix      g_matWorld;         // ��� ���̺�
matrix      g_matView;
matrix      g_matProj;

// ���÷� : �ؽ�ó�� ǰ�� �� ��� �ɼ��� �����ϴ� ����ü
sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;

	minfilter = linear;
	magfilter = linear;
};

struct VS_IN
{
	vector      vPosition   : POSITION;      // �ø�ƽ : �Ӽ� ������
	float2      vTexUV      : TEXCOORD0;
};

struct VS_OUT
{
	float4 Pos        : POSITION;
	float4 Depth    : TEXCOORD0;
};

// ���ؽ����̴�

VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.Depth = mul(vector(In.vPosition.xyz, 1.f), matWVP);

	return Out;
}


struct PS_IN
{
	float2       vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector      vColor : COLOR0;
};

// �ȼ� ���̴�

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT      Out = (PS_OUT)0;
	Out.vColor = tex2D(BaseSampler, In.vTexUV);

	/*
	1. ��� ������Ʈ�� �׸���.
	2. SSD ���ڸ� �׸���.
	3. �� �ȼ����� ��� ���̸� �о�´�.
	4. �� ���̷κ��� 3D��ġ�� ����Ѵ�.
	5. �� 3D ��ġ�� SSD ������ ���̶�� �����Ѵ�.
	6. �׷��� �ʴٸ� ��Į �ؽ�ó�� �׸���.
	*/

	/*
	�ٸ� �ȼ���� ���� ���̸� ���ؼ� ������ �ָ��ִ°��߿��� ���� �������� ã�´�.
	���� ��ġ�� �ش� �ȼ��� �����.

	��Į�� ���鶧 ������ִ¹���
	1. ���� ���� (���� �Ŀ��� �����ؼ� �ذ� �Ϲ� ���ĺ������δ� �ذ��Ҽ����� �Ŀ���� ������ �����Ͽ� �ذ��ؾ���)
	2. �����̴� ��ü�� (�׳� �����̴� ��ü�� ��Į�� �ٿ�������Ǵµ� ��Ű�׺κп��� ������ �߻� �������� �׳� �׷������� ��Į�Ⱦ��� ���Ľǹ��۷� �ذ���)
	3. ������ �þ��. (SSD���ڰ� �������� ������ �浹���� ������ �߻��ȴ�. SSD������ ��������� Gbuffer�� ���������ǰ��� Ŀ���� ������ ���ѹ�����. ������ ��Ƽ��Ʈ�� �����Ҽ��ְ� �ϴ°�����)
	(�ٸ�������δ� ���������� �̷�� ���� Ŀ���� ��Į�� ������ ������� �Ͽ����� �ձ� ������������ ���̻�)
	4. ©�� ��Į (SSD���ڰ� ī�޶� ������ �����°��)
	(ī�޶�� ��Į�� �浹�ϸ� �޸��� ��� �׷��� �ذ��Ҽ����� ���� �׽�Ʈ ���⵵ ��¤����� ������ ������ ���� �������´����� �����Ѵ�.)
	*/
	return Out;
}

technique Default_Device
{
	pass   // ����� ĸ��ȭ, PASS�� �̸��� ������� ����� ������� ������ �ε��� ���� 0�� �����ǰ� �ڵ������� �ϳ��� ������
	{
		//zwriteenable = false;
		cullmode = none;

		vertexshader = compile vs_3_0 VS_MAIN();   // ������ �Լ� ���
		pixelshader = compile ps_3_0 PS_MAIN();
	}
};