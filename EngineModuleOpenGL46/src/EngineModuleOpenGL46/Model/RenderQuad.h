#if !defined(RENDERQUAD_H)
#define RENDERQUAD_H

#include <EngineModuleOpenGL46/Drawable.h>
#include <EngineModuleOpenGL46/SystemComponent.h>

#include "Primitive.h"

class RenderQuad : public Primitive, public SystemComponent
{
public:
	RenderQuad() : Primitive("quad") {}
	bool Init() { return true; }
};

#endif