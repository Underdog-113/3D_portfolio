texture g_AlbedoTexture;
sampler AlbedoSampler = sampler_state
{
	texture = g_AlbedoTexture;
};

texture g_ShadeTexture;
sampler ShadeSampler = sampler_state
{
	texture = g_ShadeTexture;
};

texture g_SpecularTexture;
sampler SpecularSampler = sampler_state
{
	texture = g_SpecularTexture;
};

//texture g_LutTexture;
//sampler LutSampler = sampler_state
//{
//	texture = g_LutTexture;
//};

bool g_timeSlow;

//float3 GetLutColor(float3 colorIN)
//{
//	/*float u = floor(colorIN.b * 15.f) / 15.f * 240.f;
//	u = floor(colorIN.r * 15.f) + u;
//	u /= 255.f;
//
//	float v = floor(colorIN.g * 15.f) / 15.f;
//
//	float3 left = tex2D(LutSampler, float2(u, v)).rgb;
//
//	u = floor(colorIN.b * 15.f) / 15.f * 240.f;
//	u = floor(colorIN.r * 15.f) + u;
//	u /= 255.f;
//
//	v = ceil(colorIN.g * 15.f) / 15.f;
//
//	float3 right = tex2D(LutSampler, float2(u, v)).rgb;
//	
//	float3 color;
//	color.r = lerp(left.r, right.r, frac(colorIN.r * 15.f));
//	color.g = lerp(left.g, right.g, frac(colorIN.g * 15.f));
//	color.b = lerp(left.b, right.b, frac(colorIN.b * 15.f));
//
//	return color;*/
//	float2 lutSize = float2(0.00390625, 0.0625); // 1 / float2(256, 16)
//	float4 lutUV;
//	
//	colorIN = saturate(colorIN) * 15.0;
//	lutUV.w = floor(colorIN.b);
//	lutUV.xy = (colorIN.rg + 0.5) * lutSize;
//	lutUV.x += lutUV.w * lutSize.y;
//	lutUV.z = lutUV.x + lutSize.y;
//	
//	return lerp(tex2Dlod(LutSampler, lutUV.xyzz).rgb, tex2Dlod(LutSampler, lutUV.zyzz).rgb, colorIN.b - lutUV.w);
//}

struct PS_IN
{
	float2		vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector		vColor : COLOR0;
};


PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	vector vAlbedo = saturate(tex2D(AlbedoSampler, In.vTexUV));
	//vAlbedo = float4(GetLutColor(vAlbedo.rgb), 1);

	vector vShade = saturate(tex2D(ShadeSampler, In.vTexUV));
	vector vSpecular = saturate(tex2D(SpecularSampler, In.vTexUV));
	//vector a = vector(0, 0, 0, 1);
	Out.vColor = vAlbedo;// *vShade;// +vSpecular;
	

	

	return Out;
}

technique Default_Device
{
	pass
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;

		zwriteenable = false;
		vertexshader = NULL;
		pixelshader = compile ps_3_0 PS_MAIN();
	}

};
