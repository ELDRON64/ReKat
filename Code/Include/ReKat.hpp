#ifndef Rekat
#define Rekat

#ifdef ONLINE_PEER 
	#if (defined (LINUX) || defined (__linux__)) // linux implementation
		#include <Online_P/online.linux.hpp>
	#elif (defined (_WIN32) || defined (_WIN64)) // windows implementaion
		#include <Online_P/online.windows.hpp>
	#elif (defined (__APPLE__)) // mac os implementation
		#include <Online_P/online.apple.hpp>
	#endif
#elif (defined(ONLINE_SERVER))
	#if (defined (LINUX) || defined (__linux__)) // linux implementation
		#include <Online_S/online.linux.hpp>
	#elif (defined (_WIN32) || defined (_WIN64)) // windows implementaion
		#include <Online_S/online.windows.hpp>
	#elif (defined (__APPLE__)) // mac os implementation
		#include <Online_S/online.apple.hpp>
	#endif
#endif

#include <Graphik/graphik.hpp>



#endif