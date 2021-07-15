cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR;
};


texture shaderTexture;
sampler SampleType = sampler_state
{
	Texture = <shaderTexture>;
	FILTER = MIN_MAG_MIP_LINEAR;
};

PixelInputType ParticleVertexShader(VertexInputType input)
{
	PixelInputType output;


	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	// Store the particle color for the pixel shader. 
	output.color = input.color;

	return output;
}


float4 ParticlePixelShader(PixelInputType input) : SV_TARGET
{
	float4 textureColor;
	float4 finalColor;


// Sample the pixel color from the texture using the sampler at this texture coordinate location.
textureColor = tex2D(SampleType, input.tex);

// Combine the texture color and the particle color to get the final color result.
finalColor = textureColor * input.color;

return finalColor;
}

technique TShader
{
	pass p1
	{
		vertexshader = compile vs_3_0 ParticleVertexShader();
		pixelshader = compile ps_3_0 ParticlePixelShader();
	}
};