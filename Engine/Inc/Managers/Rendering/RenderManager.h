#pragma once

#include "../../CoreInc.h"


struct RenderSettings;

class Window;
class RenderDevice;


class RenderManager final : public Object
{
public:
	void Initialize() override;;

	bool RenderInit(Window& window, const RenderSettings& settings);

	void Shutdown() override;

private:
	Window* window_ = nullptr;
	RenderDevice* device_ = nullptr;
};