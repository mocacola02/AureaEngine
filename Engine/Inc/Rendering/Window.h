#pragma once

#include "../CoreInc.h"

class Input;

class Window : public Object
{
public:
	~Window() override = default;

	bool Initialize() override;

	virtual bool Create(const WindowSettings& settings) = 0;

	virtual void Destroy() = 0;

	virtual void PollEvents(Input& input) = 0;

	virtual void SetTitle(const String& title) = 0;

	virtual bool ShouldClose() const = 0;

	virtual void ApplySettings(const WindowSettings& settings) = 0;

	virtual void SetWindowMode(const WindowMode& mode) = 0;

	virtual void SetResizable(const bool enabled) = 0;
	virtual void SetSize(const uint32 width, const uint32 height) = 0;

	virtual uint32 GetWidth() const = 0;
	virtual uint32 GetHeight() const = 0;
	virtual double GetAspectRatio() const = 0;

	virtual void* GetNativeHandle() const = 0;

	virtual bool HDRRequested()		const = 0;
	virtual bool IsHDREnabled()		const = 0;
	virtual float GetHDRHeadroom()	const = 0;

	virtual bool WasHDRStateChanged() const = 0;
	virtual void ClearHDRStateChanged() = 0;
};