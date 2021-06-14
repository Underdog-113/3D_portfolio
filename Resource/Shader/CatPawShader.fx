float4x4 m_WVP;                 
float4 m_LightDir;               

texture g_BaseTex;     
sampler BaseTex = sampler_state
{
	Texture = <g_BaseTex>;
};

texture g_NormalTex;      
sampler NormalTex = sampler_state
{
	Texture = <g_NormalTex>;
};


struct VS_INPUT
{
	float4 mPosition   : POSITION0;
	float3 mNormal     : NORMAL0;
	float2 mTex		   : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 Pos    : POSITION;
	float2 Tex    : TEXCOORD0;
	float3 Normal : TEXCOORD1;
};

VS_OUTPUT VS(VS_INPUT Input)
{
	VS_OUTPUT Out;

	Out.Pos = mul(Input.mPosition, m_WVP);
	Out.Tex = Input.mTex;
	Out.Normal = normalize(Input.mNormal.xyz);

	return Out;
}

float4 PS(VS_OUTPUT In) : COLOR0
{
	float4 Out;

    // 하프 램버트 확산 조명을 통한 라이팅 계산
    float p = dot(In.Normal, -m_LightDir.xyz);
    p = p * 0.5f + 0.5;
    p = p * p;
    
    //****************************************************************
    // 툰 셰이더 처리
    //****************************************************************
    //색상 정보를 텍셀의 U 성분으로 하여 툰 맵 텍스처에서 빛 반사율을 얻음
    float4 Col = tex2D(NormalTex, float2(p, 0.0f));
    
    // 색 정보를 반환.
    Out = Col * tex2D(BaseTex, In.Tex);

return Out;
}

technique TShader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}
