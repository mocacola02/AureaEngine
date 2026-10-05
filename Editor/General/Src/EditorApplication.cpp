#include "../Inc/EditorApplication.h"

bool EditorApplication::Initialize()
{
	runtime_ = new Runtime;

	if (!runtime_)
	{
		return false;
	}

	if (!runtime_->Initialize())
	{
		return false;
	}

	return true;
}

void EditorApplication::Run() const
{
	runtime_->Run();
}

bool EditorApplication::IsRunning() const
{
	return runtime_ && runtime_->IsRunning();
}

void EditorApplication::Shutdown()
{
	if (runtime_)
	{
		runtime_->Shutdown();
		delete runtime_;
		runtime_ = nullptr;
	}
}
