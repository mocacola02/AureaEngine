#include "../Engine/Inc/Application.h"

int main()
{
	Application app;

	Log("Starting editor...");

	if (!app.Initialize())
	{
		LogAlt("Failed to initialize Application.", "Engine", "Fatal");
		return 1;
	}

	app.Run();

	const int32 result = app.GetExitCode();

	Log("Engine loop exited, shutting down...");

	app.Shutdown();

	return result;
}