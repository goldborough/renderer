#if !defined(DRAWABLE_H)
#define DRAWABLE_H

#include <EngineModuleOpenGL46/Shader/Shader.h>


class Drawable
{
private:


public:
	virtual void Draw(Shader& shader) = 0;

};

#endif