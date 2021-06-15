float m_Alpha;     // 합성률(0.0f일 때 백 버퍼 텍스처1 이미지)

sampler s0 : register(s0);   // 백버퍼 텍스처 1
sampler s1 : register(s1);   // 백버퍼 텍스처 2

struct VS_OUTPUT
{
   float4 Pos    : POSITION;
   float4 Col    : COLOR0;   
   float2 Tex    : TEXCOORD0;
};

VS_OUTPUT VS( float4 Pos      : POSITION,
              float4 Color    : COLOR0,
              float2 Tex      : TEXCOORD0 )
{
   VS_OUTPUT Out;
   
   Out.Pos = Pos;
   Out.Col = Color;
   Out.Tex = Tex;
   
   return Out;
}

float4 PS( VS_OUTPUT In ) : COLOR
{
   // 2장의 텍스처를 선형 합성
   return tex2D( s0, In.Tex ) * ( 1.0f - m_Alpha ) + tex2D( s1, In.Tex ) * m_Alpha;
}

technique TShader
{
   pass P0
   {
      VertexShader = compile vs_1_1 VS();
      PixelShader  = compile ps_1_4 PS();
   }
}