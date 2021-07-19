#include "RenderInterface.h"

RenderObject* RenderInterface::renderObject = nullptr;
unsigned int RenderInterface::SCR_WIDTH = 0;
unsigned int RenderInterface::SCR_HEIGHT = 0;

RenderInterface::RenderInterface()
{
}

RenderObject* RenderInterface::GetRenderObject()
{
	return renderObject;
}

void RenderInterface::SetRenderObject(RenderObject* o) // static
{
	if (o != nullptr) RenderInterface::renderObject = o;
}

void RenderInterface::SetDimensions(unsigned int width, unsigned int height)
{
	RenderInterface::SCR_WIDTH = width;
	RenderInterface::SCR_HEIGHT = height;
}

unsigned int RenderInterface::Width()
{
	return RenderInterface::SCR_WIDTH;
}

unsigned int RenderInterface::Height()
{
	return RenderInterface::SCR_HEIGHT;

}