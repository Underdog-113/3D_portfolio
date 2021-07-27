texture			g_AlbedoTexture;
sampler ColorSampler = sampler_state
{
	texture = g_AlbedoTexture;
};

texture			g_NormalTexture;
sampler NormalSampler = sampler_state
{
	texture = g_NormalTexture;
};

texture			g_DepthTexture;
sampler DepthSampler = sampler_state
{
	texture = g_DepthTexture;
};

matrix			g_matInvProj;
matrix			g_matInvView;

vector			g_vLightDir;
vector			g_vLightPos;
vector			g_vLightDiffuse;
vector			g_vLightAmbient;

vector			g_vGlobalAmbient;

vector			g_vMtrlDiffuse	= vector(0.588f, 0.588f, 0.588f, 1.f);
vector			g_vMtrlAmbient	= vector(0.2f, 0.2f, 0.2f, 1.f);
vector			g_vMtrlSpecular = vector(0.f, 0.f, 0.f, 1.f);

vector			g_vCamPos;
float			g_fPower;
float			g_fRange;

struct PS_IN
{
	float2	vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector		vShade		: COLOR0;
	vector		vSpecular	: COLOR1;
	vector		vLightDepth	: COLOR2;
};

PS_OUT		PS_DIRECTIONAL(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	// 텍스쳐 uv 상태의 법선 성분
	vector		vNormal		= tex2D(NormalSampler, In.vTexUV);
	vector		vColor		= tex2D(ColorSampler, In.vTexUV);
	vector		vDepth		= tex2D(DepthSampler, In.vTexUV);

	if (vNormal.a == -1)
	{
		Out.vShade = vector(0, 0, 0, 1);
		Out.vSpecular = vector(0, 0, 0, 0);
		return Out;
	}
	else if (vNormal.a == -2)
	{
		Out.vShade = vector(1, 1, 1, 1);
		Out.vSpecular = vector(0, 0, 0, 0);
		return Out;
	}
	else if (!any(vNormal))
	{
		Out.vShade = vector(1, 1, 1, 0);
		return Out;
	}
	else
	{
		vector		vNormalComplement = (vector)vNormal.a;
		// 텍스처->월드
		vNormal = vector(vNormal.xyz * 2.f - 1.f, 0.f);

		Out.vShade = saturate(dot(normalize(g_vLightDir) * -1.f, vNormal)) *
			(g_vLightDiffuse * g_vMtrlDiffuse) +
			(g_vLightAmbient * (g_vMtrlAmbient + g_vGlobalAmbient));
		Out.vShade = floor(Out.vShade * 2) / 2;
		//Out.vShade.a = 0.f;
		vector	vReflect = reflect(normalize(vector(g_vLightDir.xyz, 0.f)), vNormal);

		// vPosition : 월드 상에 존재하는 픽셀의 위치 값


		float	fViewZ = vDepth.y * 1000.f;	// 텍스처 uv 상태로 만들기 위해 far 값으로 나눠 저장했던 뷰스페이스 z값을 다시 far값을 곱해줘서 원상태로 복구

		vector		vPosition;

		// 텍스쳐 uv와 깊이 버퍼 저장한 값들을 이용해 z나누기 이전의 투영상태의 픽셀 포지션 값을 생성

		// 텍스처 U값을 투영의 x값으로 변환 0 -> -1, 1 -> 1
		vPosition.x = (In.vTexUV.x * 2.f - 1.f) * fViewZ;
		// 텍스처 V값을 투영의 y값으로 변환 0 -> 1, 1 -> -1
		vPosition.y = (In.vTexUV.y * -2.f + 1.f) * fViewZ;
		vPosition.z = vDepth.x * fViewZ;
		vPosition.w = fViewZ;

		vPosition = mul(vPosition, g_matInvProj);
		vPosition = mul(vPosition, g_matInvView);

		vector	vLook = normalize(g_vCamPos - vPosition);

		vector dotRNL = saturate(dot(normalize(vReflect), vLook));
		Out.vSpecular = pow(dotRNL, 40);
		Out.vSpecular.a = 0;
		//Out.vSpecular *= g_vMtrlSpecular;

		//Out.vSpecular = (vector)0;


		return Out;
	}
}

PS_OUT		PS_POINT(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	// 텍스쳐 uv 상태의 법선 성분
	vector		vNormal		= tex2D(NormalSampler, In.vTexUV);
	vector		vColor		= tex2D(ColorSampler, In.vTexUV);
	vector		vDepth		= tex2D(DepthSampler, In.vTexUV);

	if (vNormal.a == -1)
	{
		Out.vShade = vector(0, 0, 0, 0);
		Out.vSpecular = vector(0, 0, 0, 0);
		return Out;
	}
	else
	{
		// vPosition : 월드 상에 존재하는 픽셀의 위치 값
		float	fViewZ = vDepth.y * 1000.f;	// 텍스처 uv 상태로 만들기 위해 far 값으로 나눠 저장했던 뷰스페이스 z값을 다시 far값을 곱해줘서 원상태로 복구

		vector		vPosition;

		// 텍스쳐 uv와 깊이 버퍼 저장한 값들을 이용해 z나누기 이전의 투영상태의 픽셀 포지션 값을 생성

		// 텍스처 U값을 투영의 x값으로 변환 0 -> -1, 1 -> 1
		vPosition.x = (In.vTexUV.x * 2.f - 1.f) * fViewZ;
		// 텍스처 V값을 투영의 y값으로 변환 0 -> 1, 1 -> -1
		vPosition.y = (In.vTexUV.y * -2.f + 1.f) * fViewZ;
		vPosition.z = vDepth.x * fViewZ;
		vPosition.w = fViewZ;

		vPosition = mul(vPosition, g_matInvProj);
		vPosition = mul(vPosition, g_matInvView);


		// 텍스처->월드
		vNormal = vector(vNormal.xyz * 2.f - 1.f, 0.f);

		vector vLightDir = vPosition - g_vLightPos;
		float fDistance = length(vLightDir);

		float	fAtt = max((g_fRange - fDistance) / g_fRange, 0.f);

		Out.vShade = saturate(dot(normalize(g_vLightDir) * -1.f, vNormal)) *
			(g_vLightDiffuse * g_vMtrlDiffuse) +
			(g_vLightAmbient * (g_vMtrlAmbient + g_vGlobalAmbient)) * fAtt;
		//Out.vShade = floor(Out.vShade * 2) / 2;
		Out.vShade.a = 1.f;

		vector	vReflect = reflect(normalize(vector(vLightDir.xyz, 0.f)), vNormal);
		vector	vLook = normalize(g_vLightPos - vPosition);

		/*vector dotRNL = saturate(dot(normalize(vReflect), vLook));
		Out.vSpecular = pow(dotRNL, mtrlSpecular.a);
		Out.vSpecular.a = dotRNL.a;
		Out.vSpecular *= vector(mtrlSpecular.xyz, 1);*/
		Out.vSpecular = (vector)0;

		return Out;
	}
}

technique Default_Device
{
	pass Directional
	{
		alphablendenable = true;
		srcblend = one;
		destblend = one;

		zwriteenable = false;
		vertexshader = NULL;
		pixelshader = compile ps_3_0 PS_DIRECTIONAL();
	}

	pass Point
	{
		alphablendenable = true;
		srcblend = one;
		destblend = one;

		zwriteenable = false;
		vertexshader = NULL;
		pixelshader = compile ps_3_0 PS_POINT();
	}

};