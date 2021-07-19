#if !defined(OPENGLOBJECT_H)
#define OPENGLOBJECT_H

#include <iostream>
#include <functional>
using namespace std::placeholders;

#include <EngineUtilities/Util.h>
#include <EngineModuleOpenGL46/Control/PlatformController.h>
#include <EngineModuleOpenGL46/RenderObject.h>
#include <EngineModuleOpenGL46/RenderInterface.h>

enum RegisterFunction
{
	FRAMEBUFFER_SIZE_CALLBACK,
	CURSORPOS_CALLBACK,
	SCROLL_CALLBACK
};

class OpenGLObject : public PlatformController, public RenderObject
{
private:
	

public:
	static std::function<void(GLFWwindow* window, int width, int height)> m_framebuffer_size_callback;
	static std::function<void(GLFWwindow* window, double xpos, double ypos)> m_mouse_callback;
	static std::function<void(GLFWwindow* window, double xoffset, double yoffset)> m_scroll_callback;

	std::function<void()> m_func;

	OpenGLObject();

	bool Init();
	void Shutdown();

	void BeginScene();
	void EndScene();

	void BindFrameBuffer(unsigned int buffer_id);

	void Register(RegisterFunction flag, int f);
	

	void SetCallback_Framebuffer(std::function<void(GLFWwindow* window, int width, int height)> f);
	void SetCallback_MouseCallback(std::function<void(GLFWwindow* window, double xpos, double ypos)> f);
	void SetCallback_Scrollback(std::function<void(GLFWwindow* window, double xoffset, double yoffset)> f);



	GLFWwindow& GetWin();
};

#endif