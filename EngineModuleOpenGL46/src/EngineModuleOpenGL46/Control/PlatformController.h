#if !defined(PLATFORMCONTROLLER_H)
#define PLATFORMCONTROLLER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class PlatformController
{

protected:

	static GLFWwindow* m_window;
	bool PlatformShouldIClose();
	void SetWindow(GLFWwindow* window);

public:
	PlatformController();
	~PlatformController();

};

#endif