#pragma once
#include "DXF.h"

class TreeSegment : public BaseMesh
{


public:
	TreeSegment(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int resolution = 20);
	~TreeSegment();

protected:
	void initBuffers(ID3D11Device* device);
	int resolution;
};

