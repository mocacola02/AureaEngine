#pragma once

#include <../../Core/Core.h>


class Runtime;
class RenderDevice;
class RenderModule;

class RenderManager final : public Object
{
public:
	RenderManager() = default;
	explicit RenderManager(Runtime* runtime) : Object(runtime);

	void PreRender();
	void Render();
	void PostRender();

protected:
	friend class Runtime;
	bool Initialize() override;
	void Shutdown() override;

private:
	Runtime* engineRuntime_ = nullptr;
	RenderDevice*  renderDevice_  = nullptr;
	RenderModule*  renderModule_  = nullptr;

	static String GetRenderDevicePath();
};