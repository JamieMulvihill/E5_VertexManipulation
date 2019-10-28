// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "ManipulationShader.h"
#include "TreeSegment.h"
#include "TreeTop.h"


class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void gui();

private:
	ManipulationShader* shader;
	SphereMesh* mesh;
	SphereMesh* mesh2;
	SphereMesh* mesh3;
	SphereMesh* mesh4;
	PlaneMesh* head;
	
	Light* light;
	Light* pLight;

	TreeTop* treeHead;
	TreeSegment* treeHigh;
	TreeSegment* treeMid;
	TreeSegment* treeLow;

	float time, amplitude, frequency, speed, x, y, z;
};

#endif