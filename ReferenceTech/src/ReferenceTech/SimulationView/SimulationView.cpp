#include "SimulationView.h"

const unsigned int SimulationView::SCR_WIDTH = 1840;
const unsigned int SimulationView::SCR_HEIGHT = 1000;
vector<Shader> SimulationView::m_shaders = vector<Shader>(shaderNamesSize);
OpenGLObject* SimulationView::openGLObject = nullptr;

SimulationView::SimulationView(vector<ObjectView*>* models)
{
    deltaTime = 0.0f;
    lastFrame = 0.0f;

    m_models = models;
    
    lastX = (float)SCR_WIDTH / 2.0f;
    lastY = (float)SCR_HEIGHT / 2.0f;
    firstMouse = true;
}

SimulationView::~SimulationView()
{
}

bool SimulationView::Init()
{
    openGLObject->SetCallback_Framebuffer(std::bind(&SimulationView::framebuffer_size_callback, this, _1, _2, _3));
    openGLObject->SetCallback_MouseCallback(std::bind(&SimulationView::mouse_callback, this, _1, _2, _3));
    openGLObject->SetCallback_Scrollback(std::bind(&SimulationView::scroll_callback, this, _1, _2, _3));
    //glfwSetWindowCloseCallback

    RenderConfiguration rc = RenderConfiguration();
    rc.m_id = methodLightAO;

    m_renderSystem.SetRenderObject(*openGLObject);

    if (!m_renderSystem.Init(rc)) 
    {
        DebugPrint("m_renderSystem.Init(rc)");
        return false;
    }

    for (unsigned int i = 0; i < m_models->size(); i++)
    {
        m_models->at(i)->UpdateModelMatrix();
    }

    return true;
}

void SimulationView::Render()
{
   float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input
    // -----
    processInput(deltaTime, m_window);

    m_renderSystem.SetObjects(m_models);
    m_renderSystem.BeginRender();

    while (m_renderSystem.IsActive())
    {    
        m_renderSystem.Draw();
        m_renderSystem.Advance();
    }

    m_renderSystem.EndRender();
    
} // Render()

void SimulationView::processInput(float deltaTime, GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        BaseSubsystem::m_camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        BaseSubsystem::m_camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        BaseSubsystem::m_camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        BaseSubsystem::m_camera->ProcessKeyboard(RIGHT, deltaTime);

}

void SimulationView::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    m_renderSystem.Resize(width, height);
}

void SimulationView::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    /*
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }*/
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    BaseSubsystem::m_camera->ProcessMouseMovement(xoffset, yoffset);
}

void SimulationView::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    BaseSubsystem::m_camera->ProcessMouseScroll(yoffset);
}

