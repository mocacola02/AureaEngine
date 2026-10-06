#pragma once

#include "../../World/Inc/WorldObject.h"
#include "../Config/Inc/DisplaySettings.h"

enum class WindowMode : uint8
{
	Windowed,
	Minimized,
	Maximized,
	Fullscreen,
	ExclusiveFullscreen
};

class Input;

class Window : public WorldObject
{
public:
	~Window() override = default;

	bool Initialize() override;

	bool Show();
	bool Hide();

	void PollEvents(const Input& input);

	void SetTitle(const String& title);

	bool ShouldClose() const;

	void SetWindowMode(const WindowMode& mode);

	void SetResizable(bool enabled);
	void SetSize(uint32 width, uint32 height);

	uint32 GetWidth() const;
	uint32 GetHeight() const;
	double GetAspectRatio() const;

	void* GetNativeHandle() const;

	bool HDRRequested()	const;
	bool IsHDREnabled()	const;
	float GetHDRHeadroom() const;

	bool WasHDRStateChanged() const;
	void ClearHDRStateChanged();

private:
	bool visible_	 = true;
	bool resizable_  = true;
	bool focused_	 = true;
	bool borderless_ = false;
	bool allowUnfocusedInput_ = false;

	uint8 currentScreen_ = 0;

	String title_ = "My Cool Window";

	Vector2U size_	  = {1280, 720};
	Vector2U minSize_ = {320, 240};
	Vector2U maxSize_ = {0, 0};

	WindowMode windowMode_ = WindowMode::Windowed;

	WindowDisplaySettings displaySettings;
};