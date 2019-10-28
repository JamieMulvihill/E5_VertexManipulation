
#include "DXF.h"

class TreeTop : public BaseMesh
{


public:
	TreeTop(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int resolution = 20);
	~TreeTop();

protected:
	void initBuffers(ID3D11Device* device);
	int resolution;
};


