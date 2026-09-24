#pragma once

#include "../CoreInc.h"

struct SDL_SharedObject;
class RenderDevice;
class RenderManager;

class RenderModule : public Object
{
public:
	~RenderModule() override;

	bool Load(const String& path);
	bool IsLoaded() const;
	void Unload();

	RenderDevice* CreateDevice() const;
	void DestroyDevice(RenderDevice* device) const;

private:
	using CreateDeviceFunction  = RenderDevice*(*)();
	using DestroyDeviceFunction = void(*)(RenderDevice*);

	SDL_SharedObject* library_ = nullptr;

	CreateDeviceFunction  createDevice_ = nullptr;
	DestroyDeviceFunction destroyDevice_ = nullptr;

	RenderManager* renderManager_ = nullptr;
};