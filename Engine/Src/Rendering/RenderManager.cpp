#include "../../Inc/Rendering/RenderManager.h"

#include <SDL3/SDL.h>


bool RenderManager::Initialize()
{
	const String renderDevicePath = GetRenderDevicePath();

	return true;
}


String RenderManager::GetRenderDevicePath()
{
	#if defined(__linux__)

		return String(SDL_GetBasePath()) + "libMiraGL.so";

	#endif

	return String(SDL_GetBasePath()) + "MiraGL.dll";
}