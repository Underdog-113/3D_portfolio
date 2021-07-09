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

texture			g_SpecMtrlTexture;
sampler SpecMtrlSampler = sampler_state
{
	texture = g_SpecMtrlTexture;
};

vector			g_vLightDir;
vector			g_vLightPos;
vector			g_vLightDiffuse;
vector			g_vLightAmbient;
vector			g_vGlobalAmbient;

vector			g_vMtrlDiffuse = (vector)1.f;
vector			g_vMtrlAmbient = (vector)1.f;

vector			g_vCamPos;
float			g_fPower;
float			g_fRange;

matrix			g_matInvProj;
matrix			g_matInvView;

struct PS_IN
{
	float2	vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector		vShade		: COLOR0;
	vector		vSpecular	: COLOR1;
};

PS_OUT		PS_DIRECTIONAL(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	// 텍스쳐 uv 상태의 법선 성분
	vector		vNormal		= tex2D(NormalSampler, In.vTexUV);
	vector		vColor		= tex2D(ColorSampler, In.vTexUV);
	vector		vDepth		= tex2D(DepthSampler, In.vTexUV);
	
	

	vector mtrlDiffuse	= vector(vColor.a, vNormal.a, vDepth.z, 1.f);
	vector mtrlAmbient	= vector(vDepth.a, vDepth.a, vDepth.a, 1.f);
	vector mtrlSpecular = tex2D(SpecMtrlSampler, In.vTexUV);

	// 텍스처->월드
	vNormal = vector(vNormal.xyz * 2.f - 1.f, 0.f);
	
	Out.vShade = saturate(dot(normalize(g_vLightDir) * -1.f, vNormal)) * (g_vLightDiffuse * mtrlDiffuse) +
						 (g_vLightAmbient * (mtrlAmbient + g_vGlobalAmbient));
	Out.vShade = floor(Out.vShade * 2.5) / 2;
	Out.vShade.a = 1.f;
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


	if (mtrlSpecular.w == 0)
		mtrlSpecular.w = 20;

	vector dotRNL = saturate(dot(normalize(vReflect), vLook));
	Out.vSpecular = pow(dotRNL, mtrlSpecular.w);
	Out.vSpecular.a = 0;
	Out.vSpecular *= vector(mtrlSpecular.xyz, 1);


	return Out;
}

PS_OUT		PS_POINT(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	// 텍스쳐 uv 상태의 법선 성분
	vector		vNormal		= tex2D(NormalSampler, In.vTexUV);
	vector		vColor		= tex2D(ColorSampler, In.vTexUV);
	vector		vDepth		= tex2D(DepthSampler, In.vTexUV);

	vector mtrlDiffuse	= vector(vColor.a, vNormal.a, vDepth.z, 1.f);
	vector mtrlAmbient	= vector(vDepth.a, vDepth.a, vDepth.a, 1.f);
	vector mtrlSpecular = tex2D(SpecMtrlSampler, In.vTexUV);

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

	Out.vShade = (saturate(dot(normalize(vLightDir) * -1.f, vNormal)) * (g_vLightDiffuse * mtrlDiffuse) + 
							   (g_vLightAmbient * (mtrlAmbient + g_vGlobalAmbient))) * fAtt;
	Out.vShade.a = 1.f;

	vector	vReflect = reflect(normalize(vector(vLightDir.xyz, 0.f)), vNormal);
	vector	vLook = normalize(g_vLightPos - vPosition);

	vector dotRNL = saturate(dot(normalize(vReflect), vLook));
	Out.vSpecular = pow(dotRNL, mtrlSpecular.a);
	Out.vSpecular.a = dotRNL.a;
	Out.vSpecular *= vector(mtrlSpecular.xyz, 1);
	
	return Out;
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