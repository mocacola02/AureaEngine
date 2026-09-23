#include "Inc/Utility/Log.h"

int main()
{
	LOG("Editor ran");
	// Application app;
	//
	// LOG("Starting editor...");
	//
	// if (!app.Initialize())
	// {
	// 	ERROR("Failed to initialize Application.");
	// 	return 1;
	// }
	//
	// app.Run();
	//
	// const int32 result = app.GetExitCode();
	//
	// LOG("Engine loop exited, shutting down...");
	//
	// app.Shutdown();
	//
	// return result;
	return 0;
}


//! Exit Codes
//!
//! -1 = Generic/Unknown failure
//! 0  = Normal exit (success)
//! 1  = Failed to initialize Application.