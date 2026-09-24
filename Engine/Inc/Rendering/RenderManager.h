#pragma once

#include "../CoreInc.h"

class EngineRuntime;
class RenderDevice;
class RenderModule;

class RenderManager final : public Object
{
public:
	bool Initialize() override;
	void Shutdown() override;

	void PreRender();
	void Render();
	void PostRender();

private:
	EngineRuntime* engineRuntime_ = nullptr;
	RenderDevice*  renderDevice_  = nullptr;
	RenderModule*  renderModule_  = nullptr;

	static String GetRenderDevicePath();
};