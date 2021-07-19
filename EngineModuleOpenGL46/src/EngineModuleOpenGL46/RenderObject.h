#if !defined(RENDEROBJECT_H)
#define RENDEROBJECT_H

class RenderObject
{
protected:
	

public:
	virtual bool Init() = 0;
	virtual void Shutdown() = 0;

	virtual void BeginScene() = 0;//might change so rendersystem calls this here
	virtual void EndScene() = 0;

	virtual void BindFrameBuffer(unsigned int buffer_id) = 0;


};

#endif