#if !defined (RENDERINTERFACE_H)
#define RENDERINTERFACE_H

#include "RenderObject.h"
#include "OpenGLObject.h"



class RenderInterface
{
protected:
	static RenderObject* renderObject;

	static unsigned int SCR_WIDTH;
	static unsigned int SCR_HEIGHT;

public:
	RenderInterface();
	//todo screen size change callback?
	//RenderObject Calls static function here to execute all
	//callbacks that subscribed

	static RenderObject* GetRenderObject();
	static void SetRenderObject(RenderObject* o);

	static void SetDimensions(unsigned int width, unsigned int height);
	unsigned int Width();
	unsigned int Height();

};

#endif