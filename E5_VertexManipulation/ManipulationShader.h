#pragma once

#include "DXF.h"

using namespace std;
using namespace DirectX;

class ManipulationShader : public BaseShader
{
private:
	struct LightBufferType
	{
		XMFLOAT4 diffuse;
		XMFLOAT3 direction;
		float padding;
	};

	struct PointLightBufferType
	{
		XMFLOAT4 diffuse;
		XMFLOAT3 position;
		float padding;
	};


	struct TimeBufferType
	{ 
		float time; 
		float amplitude;
		float frequency;
		float speed;
	};

public:
	ManipulationShader(ID3D11Device* device, HWND hwnd);
	~ManipulationShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* textureTex, Light* light, Light* Ptlight, float time_, float amplitude_, float frequency_, float speed_);

private:
	void initShader(const wchar_t* cs, const wchar_t* ps);

private:
	ID3D11Buffer * matrixBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* lightBuffer;
	ID3D11Buffer* pointlightBuffer;
	ID3D11Buffer* timeBuffer;
};

