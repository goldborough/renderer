#include "RenderSystem.h"

RenderSystem::RenderSystem()
{
    m_objectCreator =
    {
        {SysCompRenderQuad,      []() { return(SystemComponent*)new RenderQuad();       }},
        {SysCompGeometryBuffer,  []() { return(SystemComponent*)new GeometryBuffer();   }},
        {SysCompDepthBuffer,     []() { return(SystemComponent*)new DepthBuffer();      }},
        {SysCompSSAOColorBuffer, []() { return(SystemComponent*)new SSAOColorBuffer();  }},
        {SysCompSSAOBlurBuffer,  []() { return(SystemComponent*)new SSAOBlurBuffer();   }}
    };

    m_shaderObjectCreator = 
    {
        {shaderGeometryPass,       []() {
                return Shader("resources/shaders/35_ssao_geometry.vs.glsl", "resources/shaders/35_ssao_geometry.fs.glsl"); }},
        {shaderLightingPass,       []() {
                return Shader("resources/shaders/35_ssao.vs.glsl", "resources/shaders/35_ssao_lighting.fs.glsl"); }},
        {shaderSSAO,               []() {
                return Shader("resources/shaders/35_ssao.vs.glsl", "resources/shaders/35_ssao.fs.glsl"); }},
        {shaderSSAOBlur,           []() {
                return Shader("resources/shaders/35_ssao.vs.glsl", "resources/shaders/35_ssao_blur.fs.glsl"); }}
    };
}

RenderSystem::~RenderSystem()
{
    map<SystemComponentType, SystemComponent*>::iterator iter = m_componentMap.begin();

    while (iter != m_componentMap.end())
    {
        delete iter->second;
        iter->second = nullptr;
        iter = m_componentMap.erase(iter);//next iterator is returned
    }
    
    for (unsigned int i = 0; 0 < m_allSubsystemInstances.size(); i++)
    {
        delete m_allSubsystemInstances.at(i);
        m_allSubsystemInstances.at(i) = nullptr;
    }

    delete m_quad;
    m_quad = nullptr;
}


bool RenderSystem::Init(const RenderConfiguration& config)
{
    m_state = renderSystemInactive;

    //renderquad
    std::pair< SystemComponentType, std::function<SystemComponent* ()> > pair = *m_objectCreator.find(SysCompRenderQuad);
    SystemComponent* quad = pair.second();
    m_componentMap.insert(std::make_pair(SysCompRenderQuad, quad));
    m_quad = (RenderQuad*) quad;

    //init subsystems
    if (config.m_id == methodLightAO)
    {
        BaseSubsystem * subsystem = new AmbientOcclusionSubsystem();

        std::vector <SystemComponentType> * recipe = subsystem->GetRecipe();
       
        for (size_t i = 0; i < recipe->size(); i++ )
        {
            if (m_componentMap.find(recipe->at(i)) == m_componentMap.end())
            {   
                std::pair< SystemComponentType, std::function<SystemComponent* ()> > f = *m_objectCreator.find(recipe->at(i));
                SystemComponent* component = f.second();
                m_componentMap.insert(std::make_pair(recipe->at(i), component));
            }
        }

        std::vector <ShaderNames>* shaderRecipe = subsystem->GetShaderRecipe();

        for (size_t i = 0; i < shaderRecipe->size(); i++)
        {
            if (m_shaderComponentMap.find(shaderRecipe->at(i)) == m_shaderComponentMap.end())
            {
                std::pair< ShaderNames, std::function<Shader()> > f = *m_shaderObjectCreator.find(shaderRecipe->at(i));
                Shader * s = new Shader(f.second());
                m_shaderComponentMap.insert(std::make_pair(shaderRecipe->at(i), s ));
            }
        }

        subsystem->Init(m_componentMap,m_shaderComponentMap);
        m_allSubsystemInstances.push_back(subsystem);
        m_renderPassVector.push_back(subsystem);
    }

    m_camera = Camera(LMVector3(0.0f, 0.0f, 5.0f));

    BaseSubsystem::SetCamera(&m_camera);

    m_ao = (AmbientOcclusionSubsystem*)m_renderPassVector.at(0);

    //main2((OpenGLObject*)m_renderObject);

    return true;
}

//manual hardcode for testing only

#ifdef _DEBUG
void RenderSystem::Render2()
{
    BeginRender();

    m_ao->Draw(m_objectViews);
    m_ao->OnExitGeometry();

    m_ao->OnEnterSSAOTexturePass();
    m_ao->Draw(m_objectViews);
    m_ao->OnExitSSAOTexturePass();

    m_ao->OnEnterSSAOTextureBlurPass();
    m_ao->Draw(m_objectViews);
    m_ao->OnExitSSAOTextureBlurPass();

    m_ao->OnEnterLightingPass();
    m_ao->Draw(m_objectViews);
    m_ao->OnExitLightingPass();

    EndRender();
}
#endif

void RenderSystem::BeginRender()
{
    m_state = renderSystemActive;
    m_renderObject->BeginScene();

    m_currentSubsystem = m_renderPassVector.at(m_currentSubsystemIndex = 0);
    m_currentSubsystem->Activate();
}

void RenderSystem::EndRender()
{
    m_renderObject->EndScene();
}

bool RenderSystem::IsActive()
{
    return (m_state == renderSystemActive) ? true : false;
}

void RenderSystem::Advance()
{
    if (SubsystemCanAdvance()) SubsystemAdvance();
    else if (RenderSystemCanAdvance()) RenderSystemAdvance();
    else
    {
        m_state = renderSystemInactive;
    }
}

void RenderSystem::SetObjects(vector<ObjectView*>* objectViews)
{
    m_objectViews = objectViews;//todo no
}

void RenderSystem::Draw()
{
    m_currentSubsystem->Draw(m_objectViews);//todo no
}

void RenderSystem::Resize(int width, int height)
{
    m_nextDimensions = LMVector2(width, height);
}

void RenderSystem::SetRenderObject(RenderObject& renderObject)
{
    m_renderObject = &renderObject;
}

// private:
bool RenderSystem::RenderSystemCanAdvance()
{
    m_currentSubsystem->SubSystemExitCurrentState();

    return (m_currentSubsystemIndex + 1 < (int)m_renderPassVector.size() - 1)
        ? true : false;
}

void RenderSystem::RenderSystemAdvance()
{
    m_renderPassVector.at(m_currentSubsystemIndex)->Deactivate();
    m_renderPassVector.at(++m_currentSubsystemIndex)->Activate();
}

// private:
bool RenderSystem::SubsystemCanAdvance()
{
    return (m_renderPassVector.at(m_currentSubsystemIndex)->CanAdvance())
        ?  true : false;
}

// private:
void RenderSystem::SubsystemAdvance()
{
    m_renderPassVector.at(m_currentSubsystemIndex)->Advance();
}
