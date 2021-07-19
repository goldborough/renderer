#include "ObjectView.h"

ObjectView::ObjectView(Primitive& model)
{
    m_primitive = &model;
    m_drawable = &model;
}

ObjectView::ObjectView(Model& model)
{
    SetModel(model);
}

void ObjectView::SetModel(Model& model)
{
    m_model = &model;
    m_drawable = &model;
}

void ObjectView::AddProperty(std::string string, int value)
{
    m_properties.push_back(Property(string,value));
}

const vector<Property>* ObjectView::GetProperties()
{
    return &m_properties;
}

bool ObjectView::FindProperty(Property* p)
{
    bool found = false;

    // Iterate over all elements in Vector
    for (auto& elem : m_properties)
    {
        if (elem.m_fieldName == p->m_fieldName)
        {
            p->m_fieldValue = elem.m_fieldValue;
            return true;
        }
    }

    return false;
}

void ObjectView::Draw(Shader& shader)
{
    m_drawable->Draw(shader);
}

void ObjectView::UpdateModelMatrix()
{
    m_modelMatrix = LMMatrix4(1.0f);
    m_modelMatrix.translate_mesh(m_translation);
    if (m_rotation !=0) m_modelMatrix.rotate_mesh(m_rotation, m_rotationAxis);
    m_modelMatrix.scale_mesh(m_scale);
}

LMMatrix4* ObjectView::GetModelMatrix()
{
    return &m_modelMatrix;
}

void ObjectView::Set(LMVector3 t, float r, LMVector3 a, LMVector3 s)
{
    m_translation = t;
    m_rotation = MyMath::radians(r);
    m_rotationAxis = a;
    m_scale = s;
    UpdateModelMatrix();
}