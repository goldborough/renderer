#include "OpenGLObject.h"

std::function<void(GLFWwindow* window, int width, int height)> OpenGLObject::m_framebuffer_size_callback = nullptr;
std::function<void(GLFWwindow* window, double xpos, double ypos)> OpenGLObject::m_mouse_callback = nullptr;
std::function<void(GLFWwindow* window, double xoffset, double yoffset)> OpenGLObject::m_scroll_callback = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

OpenGLObject::OpenGLObject()
{

}

bool OpenGLObject::Init()
{
    int SCR_WIDTH = 1840;
    int SCR_HEIGHT = 1000;

    RenderInterface::SetRenderObject(this);
    RenderInterface::SetDimensions(SCR_WIDTH, SCR_HEIGHT);

    // glfw: initialize and configure
// ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    this->Register(FRAMEBUFFER_SIZE_CALLBACK, (int)&framebuffer_size_callback);
    this->Register(CURSORPOS_CALLBACK, (int)&mouse_callback);
    this->Register(SCROLL_CALLBACK, (int)&scroll_callback);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowPos(m_window, 0, 1150);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);

	return true;
}

void OpenGLObject::Shutdown()
{
}

void OpenGLObject::BeginScene()
{
    DebugPrint("OpenGLObject::BeginScene()");
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLObject::EndScene()
{
    DebugPrint("OpenGLObject::EndScene()");
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void OpenGLObject::BindFrameBuffer(unsigned int buffer_id)
{
    glBindFramebuffer(GL_FRAMEBUFFER, buffer_id);
}

void OpenGLObject::Register(RegisterFunction flag, int f)
{
    switch (flag)
    {
    case FRAMEBUFFER_SIZE_CALLBACK:
        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
        break;
    case SCROLL_CALLBACK:
        glfwSetScrollCallback(m_window, scroll_callback);
        break;
    case CURSORPOS_CALLBACK:
        glfwSetCursorPosCallback(m_window, mouse_callback);
        break;
        //glfwSetWindowCloseCallback
    default:
        break;
    }
}

void OpenGLObject::SetCallback_Framebuffer(std::function<void(GLFWwindow* window, int width, int height)> f)
{
    OpenGLObject::m_framebuffer_size_callback = f;
}

void OpenGLObject::SetCallback_MouseCallback(std::function<void(GLFWwindow* window, double xpos, double ypos)> f)
{
    OpenGLObject::m_mouse_callback = f;
}

void OpenGLObject::SetCallback_Scrollback(std::function<void(GLFWwindow* window, double xoffset, double yoffset)> f)
{
    OpenGLObject::m_scroll_callback = f;
}

GLFWwindow& OpenGLObject::GetWin()
{
    return *m_window;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void  framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (OpenGLObject::m_framebuffer_size_callback != nullptr)
    {
        OpenGLObject::m_framebuffer_size_callback(window, width,height);
        return;
    }
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void  mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (OpenGLObject::m_mouse_callback != nullptr)
    {
        OpenGLObject::m_mouse_callback(window, xpos, ypos);
        return;
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void  scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (OpenGLObject::m_scroll_callback != nullptr)
    {
        OpenGLObject::m_scroll_callback(window, xoffset, yoffset);
        return;
    }

}