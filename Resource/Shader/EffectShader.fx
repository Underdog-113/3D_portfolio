matrix		g_matWorld;	  // ��� ���̺�
matrix		g_matView;
matrix		g_matProj;

float       g_BlendColor; // blend Color Factor
texture		g_BaseTexture;
sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;
};

texture		g_AlphaMaskTex;
sampler AlphaMaskSampler =  sampler_state
{
	texture = g_AlphaMaskTex;
};

struct PS_INPUT
{
	float2 TexCoord : TEXCOORD0;
};

float4 PS_MAIN(PS_INPUT Input) : COLOR0
{
	return clamp(tex2D(BaseSampler, Input.TexCoord) + tex2D(AlphaMaskSampler, Input.TexCoord) * abs(g_BlendColor), 0, 1);
}


technique Default_Device
{
	pass	// ����� ĸ��ȭ, PASS�� �̸��� ������� ����� ������� ������ �ε��� ���� 0�� �����ǰ� �ڵ������� �ϳ��� ������
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;

		pixelshader = compile ps_3_0 PS_MAIN();
	}

	pass	
	{
		pixelshader = compile ps_3_0 PS_MAIN();
	}

};