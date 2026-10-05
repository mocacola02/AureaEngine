#pragma once

#include <Engine.h>


class EditorApplication final : public Application
{
public:
	~EditorApplication() override = default;

	//! Creates and initializes the runtime.
	bool Initialize() override;

	//! Application loop that ticks the runtime.
	void Run() const override;

	bool IsRunning() const override;

	//! Shuts down and destroys the runtime.
	void Shutdown() override;

private:
	Runtime* runtime_ = nullptr;
};