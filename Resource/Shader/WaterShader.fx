
float4x4 g_mWVP;		// ��ǥ��ȯ ���

float4 g_vLightDir;		// ��������
float4 g_vColor;		// ����*�޽� ��
float3 g_vEyePos;		// ī�޶���ġ(������ǥ��)

					// -------------------------------------------------------------
					// �ؽ�ó
					// -------------------------------------------------------------
					// ���� �ؽ�ó
texture g_DecaleTex;
sampler DecaleSamp = sampler_state
{
	Texture = <g_DecaleTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;

	//AddressU = Clamp;
	//AddressV = Clamp;
};
// -------------------------------------------------------------
// ������
texture g_NormalMap;
sampler NormalSamp = sampler_state
{
	Texture = <g_NormalMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;

	/*AddressU = Wrap;
	AddressV = Wrap;*/
};

// -------------------------------------------------------------
// �������̴����� �ȼ����̴��� �ѱ�� ������
// -------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos			: POSITION;
	float4 Color		: COLOR0;		// ������
	float2 Tex			: TEXCOORD0;	// �����ؽ�ó ��ǥ
	float3 L			: TEXCOORD1;	// ��������
	float3 E			: TEXCOORD2;	// ��������
};
// -------------------------------------------------------------
// ��鷻��
// -------------------------------------------------------------
VS_OUTPUT VS(
	float4 Pos      : POSITION,          // ������ġ��ǥ
	float3 Normal	: NORMAL,            // ��������
	float3 Tangent	: TANGENT0,          // ��������
	float2 Texcoord : TEXCOORD0          // �ؽ�ó��ǥ
) {
	VS_OUTPUT Out = (VS_OUTPUT)0;        // ��µ�����

										 // ��ǥ��ȯ
	Out.Pos = mul(Pos, g_mWVP);

	// �޽� ��
	Out.Color = 1.f;

	// ���ÿ� �ؽ�ó��ǥ
	Out.Tex = Texcoord;

	// ��ǥ�躯ȯ ����
	float3 N = Normal;
	float3 T = Tangent;
	float3 B = cross(N, T);

	// �ݿ��ݻ�� ����
	float3 E = g_vEyePos - Pos.xyz;	// �ü�����
	Out.E.x = dot(E, T);
	Out.E.y = dot(E, B);
	Out.E.z = dot(E, N);

	float3 L = -g_vLightDir.xyz;		// ��������
	Out.L.x = dot(L, T);
	Out.L.y = dot(L, B);
	Out.L.z = dot(L, N);

	return Out;
}
// -------------------------------------------------------------
float4 PS(VS_OUTPUT In) : COLOR
{
	float3 N = 2.0f * tex2D(NormalSamp, In.Tex).xyz - 1.0;// ���������κ��� ����
	float3 L = normalize(In.L);						    // ��������
	float3 R = reflect(-normalize(In.E), N);			// �ݻ纤��
	float amb = -g_vLightDir.w;							// ȯ�汤�� ����

	return In.Color * tex2D(DecaleSamp, In.Tex)	// Ȯ�걤�� ȯ�汤��
		* (max(0, dot(N, L)) + amb)			// �������� �ؽ�ó���� �ռ��Ѵ�
		+ 0.7f * pow(max(0,dot(R, L)), 8);		// Phong�ݿ��ݻ籤
}

// -------------------------------------------------------------
// ��ũ��
// -------------------------------------------------------------
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}
