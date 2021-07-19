#if !defined (OBJECTVIEW_H)
#define OBJECTVIEW_H

#include <vector>
#include <string>

#include <EngineUtilities/Math.h>
#include <EngineModuleOpenGL46/Model/Model.h>
#include <EngineModuleOpenGL46/Model/Primitive.h>

struct Property
{
	std::string m_fieldName = "";
	int m_fieldValue;

	Property(std::string fieldName, int fieldValue)
	{
		m_fieldName = fieldName;
		m_fieldValue = fieldValue;
	}
};

class ObjectView
{
private:
	Primitive * m_primitive;
	Model * m_model;
	Drawable * m_drawable;
	
	std::vector<Property> m_properties;

	LMMatrix4 m_modelMatrix;
	LMVector3 m_translation;
	float m_rotation;
	LMVector3 m_rotationAxis;
	LMVector3 m_scale;
public:

	ObjectView(Primitive& model);
	ObjectView(Model& model);
	void SetModel(Model& model);
	void SetPrimitive(Primitive& primitive);
	void AddProperty(std::string string ,int value);
	const std::vector<Property> * GetProperties();
	bool FindProperty(Property * p);
	void Draw(Shader &shader);

	void UpdateModelMatrix();
	LMMatrix4* GetModelMatrix();
	void Set(LMVector3 t, float r, LMVector3 a, LMVector3 s);
};

#endif