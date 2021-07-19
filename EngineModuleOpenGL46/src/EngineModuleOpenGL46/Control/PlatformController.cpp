#include "PlatformController.h"

GLFWwindow* PlatformController::m_window = nullptr;

PlatformController::PlatformController()
{

}
PlatformController::~PlatformController()
{
}

bool PlatformController::PlatformShouldIClose()
{
	return glfwWindowShouldClose(m_window);
}

void PlatformController::SetWindow(GLFWwindow* window)
{
	m_window = window;
}