#include "../../Inc/Rendering/RenderModule.h"

#include <SDL3/SDL.h>


RenderModule::~RenderModule()
{
	Unload();
}

bool RenderModule::Load(const String& path)
{
	if (library_)
	{
		WARN("A render module is already loaded.");
		return false;
	}

	library_ = SDL_LoadObject(path.CStr());

	if (!library_)
	{
		const String errorHeader = "SDL encountered a fatal error when loading render module library: ";

		if (const String sdlError = String(SDL_GetError()); !sdlError.IsEmpty())
		{
			ERROR(errorHeader + sdlError);
		}
		else
		{
			ERROR(errorHeader + "Unknown error.");
		}

		return false;
	}

	createDevice_  = reinterpret_cast<CreateDeviceFunction>(SDL_LoadFunction(library_, "CreateRenderDevice"));
	destroyDevice_ = reinterpret_cast<DestroyDeviceFunction>(SDL_LoadFunction(library_, "DestroyRenderDevice"));

	if (!createDevice_ || !destroyDevice_)
	{
		const String errorHeader = "SDL encountered a fatal error when assigning functions: ";

		if (const String sdlError = String(SDL_GetError()); !sdlError.IsEmpty())
		{
			ERROR(errorHeader + sdlError);
		}
		else
		{
			ERROR(errorHeader + "Unknown error.");
		}

		Unload();

		return false;
	}

	return true;
}

bool RenderModule::IsLoaded() const
{
	return library_ != nullptr;
}

void RenderModule::Unload()
{
	createDevice_  = nullptr;
	destroyDevice_ = nullptr;

	if (library_)
	{
		SDL_UnloadObject(library_);
		library_ = nullptr;
	}
}

RenderDevice* RenderModule::CreateDevice() const
{
	if (!createDevice_)
	{
		return nullptr;
	}

	return createDevice_;
}

void RenderModule::DestroyDevice(RenderDevice* device) const
{
	if (!device || !destroyDevice_)
	{
		return;
	}

	destroyDevice_(device);
}


