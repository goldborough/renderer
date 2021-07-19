#include "SimulationViewFactory.h"

SimulationViewFactory::SimulationViewFactory()
{

}

SimulationViewFactory::~SimulationViewFactory()
{
}

/*
SimulationView::m_shaders.resize(0);

//shaderGeometryPass
SimulationView::m_shaders.push_back( Shader("resources/shaders/35_ssao_geometry.vs.glsl", "resources/shaders/35_ssao_geometry.fs.glsl"));
//shaderLightingPass
SimulationView::m_shaders.push_back( Shader("resources/shaders/35_ssao.vs.glsl", "resources/shaders/35_ssao_lighting.fs.glsl"));
//shaderSSAO
SimulationView::m_shaders.push_back( Shader("resources/shaders/35_ssao.vs.glsl", "resources/shaders/35_ssao.fs.glsl"));
//shaderSSAOBlur
SimulationView::m_shaders.push_back( Shader("resources/shaders/35_ssao.vs.glsl", "resources/shaders/35_ssao_blur.fs.glsl"));
*/

SimulationView * SimulationViewFactory::GetView(SimulationConfig* config)
{
    m_objectViews.resize(0);
   
    //hard code
    vector<ObjectView*>* models = new vector<ObjectView*>();

    //hard code

    Primitive* p = new Primitive("cube");
    ObjectView* o = new ObjectView(*p);
    ObjectView* cubeView = o;

    o->AddProperty("visible", 1);
    o->AddProperty("receivesSSAO", 1);
    o->AddProperty("invertNormals", 1);
    o->Set(LMVector3(0.0f, 7.0f, 0.f), 0.f, LMVector3(1.f, 0.0f, 0.0f), LMVector3(7.5f, 7.5f, 7.5f));//	void Set(LMVector3 t, float r, LMVector3 a, LMVector3 s);

    models->push_back(o);

    //backpack mesh

    Model * backpack = new Model("resources/objects/sponza/sponza.obj");
    o = new ObjectView(*backpack);
    o->AddProperty("visible", 1);
    o->AddProperty("receivesSSAO", 1);
    o->Set(LMVector3(0.f, -0.1f, 0.f), -0.01f, LMVector3(1.f, 0.f, 0.f), LMVector3(0.002f));
    models->push_back(o);

    return new SimulationView(models);
}

ObjectView* SimulationViewFactory::RetrieveModel(string path)
{
    Model* m = new Model(path);

    ObjectView* o = new ObjectView(*m);

    m_objectViews.push_back(o);

    return o;
}

ObjectView* SimulationViewFactory::RetrievePrimitive(string type)
{
    Primitive* p = new Primitive(type);

    ObjectView* o = new ObjectView(*p);

    m_objectViews.push_back(o);

    return o;
}
