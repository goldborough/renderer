#if !defined(SIMULATIONVIEW_H)
#define SIMULATIONVIEW_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <random>

#include <functional>
using namespace std::placeholders;

#include <EngineUtilities/View/camera.h>
#include <EngineUtilities/Util.h>

#include <EngineModuleOpenGL46/RenderSystem.h>
#include <EngineModuleOpenGL46/Control/PlatformController.h>
#include <EngineModuleOpenGL46/OpenGLObject.h>

#include <EngineModuleOpenGL46/ObjectView.h>


class SimulationView : PlatformController
{
public:
	static OpenGLObject * openGLObject;
	static vector<Shader> m_shaders;

	static const unsigned int SCR_WIDTH;
	static const unsigned int SCR_HEIGHT;

private:
	RenderSystem m_renderSystem;

	vector<ObjectView*> * m_models;
	
	//Camera m_camera;
	float lastX;
	float lastY;
	bool firstMouse;

	float deltaTime;
	float lastFrame;

public:
	SimulationView(vector<ObjectView*>* models);
	~SimulationView();

	bool Init();

	void Render();

	void processInput(float deltaTime, GLFWwindow * window);

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

};

#endif