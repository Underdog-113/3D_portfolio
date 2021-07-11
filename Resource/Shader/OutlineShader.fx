matrix		g_matWorld;
matrix		g_matView;
matrix		g_matProj;

struct VS_IN
{
	vector		vPosition   : POSITION;
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
};

struct VS_OUT
{
	vector		vPosition   : POSITION;
};

struct PS_IN
{
};

struct PS_OUT
{
	vector		vColor : COLOR0;
	vector		vNormal : COLOR1;
	vector		vDepth : COLOR2;
};

VS_OUT VS_OUTLINE(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.vPosition = mul(vector(In.vPosition.xyz, 1.f), matWVP);
	Out.vPosition += (normalize(mul(vector(In.vNormal.xyz, 0.f), matWVP)) / 220);

	return Out;
}


PS_OUT PS_OUTLINE(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	Out.vColor = float4(0, 0, 0, 1);
	Out.vNormal = float4(0, 0, 0, -1);
	Out.vDepth = float4(0, 0, 0, 0);
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
};