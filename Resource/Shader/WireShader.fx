matrix		g_matWorld;
matrix		g_matView;
matrix		g_matProj;

float4		g_color;

struct VS_IN
{
	vector		vPosition   : POSITION;
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
};

struct VS_OUT
{
	vector		vPosition : POSITION;
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
};

// ???ؽ????̴?
VS_OUT		VS_MAIN(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.vPosition = mul(vector(In.vPosition.xyz, 1.f), matWVP);
	Out.vNormal = normalize(mul(vector(In.vNormal.xyz, 0.f), g_matWorld));

	Out.vTexUV = In.vTexUV;

	return Out;
}

struct PS_IN
{
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
};

struct PS_OUT
{
	vector		vColor : COLOR0;
	vector		vNormal : COLOR1;
	vector		vDepth : COLOR2;
};

// ?ȼ? ???̴?

PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor = g_color;
	vector normal = In.vNormal;
	Out.vNormal = vector(0,0,0,-1);
	
	Out.vDepth = (vector)0;

	return Out;
}


technique Default_Device
{
	pass
	{
		fillmode = wireframe;
		cullmode = none;
		vertexshader = compile vs_3_0 VS_MAIN();
		pixelshader = compile ps_3_0 PS_MAIN();
	}
};