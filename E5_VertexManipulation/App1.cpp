// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"

App1::App1()
{
	mesh = nullptr;
	shader = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	//textureMgr->loadTexture(L"brick", L"res/height.png");
	textureMgr->loadTexture(L"waterHeight", L"res/WaterHeight2.png");
	textureMgr->loadTexture(L"waterTex", L"res/WaterTex.png");
	textureMgr->loadTexture(L"Gold", L"res/Blob.png");
	textureMgr->loadTexture(L"Mount", L"res/mapTex.png");
	textureMgr->loadTexture(L"Mount_Height", L"res/height.png");
	textureMgr->loadTexture(L"brick", L"res/brick1.dds");
	textureMgr->loadTexture(L"brick_nor", L"res/brick_bump.png");
	textureMgr->loadTexture(L"black", L"res/black.png");

	// Create Mesh object and shader object
	mesh = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext());
	shader = new ManipulationShader(renderer->getDevice(), hwnd);
	light = new Light;
	pLight = new Light;

	pLight->setDiffuseColour(1, 1, 1, 1);
	pLight->setPosition(50, 10, 50);

	x = 0.7f;
	y = -.7f;
	z = 0.f;

	light->setDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	light->setDirection(x, y, z);

	time = 0.f;
	amplitude = 1;
	frequency =1;
	speed = 1;
}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D object.
	if (mesh)
	{
		delete mesh;
		mesh = 0;
	}

	if (shader)
	{
		delete shader;
		shader = 0;
	}
}


bool App1::frame()
{
	bool result;

	
	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}
	
	light->setDirection(x, y, z);
	time += timer->getTime();

	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool App1::render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->update();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	worldMatrix = renderer->getWorldMatrix();
	viewMatrix = camera->getViewMatrix();
	projectionMatrix = renderer->getProjectionMatrix();

	// Send geometry data, set shader parameters, render object with shader
	mesh->sendData(renderer->getDeviceContext());
	//shader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"waterHeight"), textureMgr->getTexture(L"waterTex"), light, time, amplitude, frequency, speed);
	shader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"Mount_Height"), textureMgr->getTexture(L"Mount_Height"), light, pLight, time, amplitude, frequency, speed);
	shader->render(renderer->getDeviceContext(), mesh->getIndexCount());

	// Render GUI
	gui();

	// Swap the buffers
	renderer->endScene();

	return true;
}

void App1::gui()
{
	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Checkbox("Wireframe mode", &wireframeToggle);
	ImGui::SliderFloat("Ampliude", &amplitude, 0, 15.f);
	ImGui::SliderFloat("Frequency", &frequency, 0, 15.f);
	ImGui::SliderFloat("Speed", &speed, 0, 15.f);
	ImGui::SliderFloat("X", &x, -1, 1);
	ImGui::SliderFloat("Y", &y, -1, 1);
	ImGui::SliderFloat("Z", &z, -1, 1);
	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

