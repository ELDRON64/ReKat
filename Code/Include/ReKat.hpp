#ifndef Rekat
#define Rekat

#if (defined (LINUX) || defined (__linux__)) // linux implementation
	#include <Online/online.linux.hpp>
#elif (defined (_WIN32) || defined (_WIN64)) // windows implementaion
	#include <Online/online.windows.hpp>
#elif (defined (__APPLE__)) // mac os implementation
	#include <Online/online.apple.hpp>
#endif

#endif