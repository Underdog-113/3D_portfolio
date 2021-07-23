texture g_FinalTexture;
sampler FinalSampler = sampler_state
{
	texture = g_FinalTexture;
};


struct PS_IN
{
	float2		vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector		vColor : COLOR;
};


PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor = saturate(tex2D(FinalSampler, In.vTexUV));

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
