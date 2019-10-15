// Light vertex shader
// Standard issue vertex shader, apply matrices, pass info to pixel shader
Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer TimeBuffer : register(b1)
{
	float time;
	float amplitude;
	float frequency;
	float speed;
};

struct InputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct OutputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

float4 ApplyHeightMap(float4 position, float3 normal, float2 tex, int height) {

	//float textureColor = texture0.SampleLevel(sampler0, tex, 0);

	//float offest = (textureColor * 1);
	//position.y += normal.y * offest;
	//position.x += normal.x * offest;
	//position.z += normal.z * offest;

	//return position;
}
float3 calcNormals(float3 position) {


	/*//offset position based on sine wave
	//input.position.y = amplitude*sin((input.position.x * frequency) + (time* speed));
	//input.position.y += amplitude * cos((input.position.z * frequency) + (time * speed));
	//modify normals
	input.normal.x = 1 - amplitude * cos((input.position.x * frequency) + (time * speed));
	input.normal.y = abs(amplitude * cos((input.position.x * frequency) + (time * speed)));*/

	float3 neighbourS, neighbourW, neighbourN, neighbourE, vectorSouth, vectorWest, vectorEast, vectorNorth, resultSW, resultSE, resultNE, resultNW, finalNormal;

	neighbourS.x = position.x;
	neighbourS.y = position.y;
	neighbourS.z = position.z - 1;
	//neighbourS.y = amplitude * sin((neighbourS.x * frequency) + (time * speed));// + amplitude * cos((neighbourS.z * frequency) + (time * speed));
	
	neighbourW.x = position.x - 1;
	neighbourW.y = position.y;
	neighbourW.z = position.z;
	//neighbourW.y = amplitude * sin((neighbourW.x * frequency) + (time * speed));// +amplitude * cos((neighbourW.z * frequency) + (time * speed));
	
	neighbourE.x = position.x + 1;
	neighbourE.y = position.y;
	neighbourE.z = position.z;
	//neighbourE.y = amplitude * sin((neighbourE.x * frequency) + (time * speed));// +amplitude * cos((neighbourE.z * frequency) + (time * speed));
	
	neighbourN.x = position.x;
	neighbourN.y = position.y;
	neighbourN.z = position.z + 1;
//	neighbourN.y = amplitude * sin((neighbourN.x * frequency) + (time * speed));// +amplitude * cos((neighbourN.z * frequency) + (time * speed));
	
	vectorSouth = normalize(neighbourS - position);
	vectorWest = normalize(neighbourW - position);
	vectorEast = normalize(neighbourE - position);
	vectorNorth = normalize(neighbourN - position);
	
	resultSW = cross(vectorSouth, vectorWest);
	resultSE = cross(vectorEast, vectorSouth);
	resultNW = cross(vectorWest, vectorNorth);
	resultNE = cross(vectorNorth, vectorEast);
	
	//resultSW = cross(neighbourS, neighbourW);
	//resultSE = cross(neighbourE, neighbourS);
	//resultNW = cross(neighbourW, neighbourN);
	//resultNE = cross(neighbourN, neighbourE);
	
	finalNormal = (resultSW + resultSE + resultNE + resultNW) / 4;


	return finalNormal;
}

OutputType main(InputType input)
{
	OutputType output;

	//offset position based on sine wave
	//input.position.y = amplitude*sin((input.position.x * frequency) + (time* speed));
	//input.position.y += amplitude * cos((input.position.z * frequency) + (time * speed));
	
	//modify normals

	//z = s, x = t
	//float3 dr/dt = float3(2t, s, s ^ 2 - 2st);
	//float3 dr/ds float3(-2s, t, 2ts -t^2)
	//float3 normalResult = cross( dr/dt, dr/ds)

	/*float3 xDerivative = float3(2 * input.position.x, input.position.z, pow(input.position.z, 2) -2 * (input.position.z * input.position.x));
	float3 zDerivative = float3(-2 * input.position.z, input.position.x, (2 *(input.position.x * input.position.z)) - pow(input.position.x, 2));
	float3 result = cross(zDerivative, xDerivative);
	input.normal = result;*/

	input.normal = calcNormals(input.position);

	////input.position.xyz += input.normal * (amplitude * sin((input.position.x * frequency) + (time * speed)));// +amplitude * cos((input.position.z * frequency) + (time * speed)));
	//input.position.y += input.normal.y;
	//input.position.x += input.normal.x;
	//input.position.z += input.normal.z;

	float textureColor = texture0.SampleLevel(sampler0, input.tex, 0);
	float offest = (textureColor * 35);
	input.position.y += input.normal.y * offest;
	input.position.x += input.normal.x * offest;
	input.position.z += input.normal.z * offest;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	// Calculate the normal vector against the world matrix only and normalise.
	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	return output;
}