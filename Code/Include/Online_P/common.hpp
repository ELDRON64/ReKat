#ifndef ONLINE_COMMON
#define ONLINE_COMMON

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <time.h>
// #include "crypt_core.hpp"

namespace ReKat {
namespace online {
	#define DPORT 42069
	#define DPORT_W "42069"
	#define DTIMEOUT 1
	#define BUF_LEN 32
	
	enum Status {
		SUCCESS,
		FAILURE,
		FAILED_WSADATA,
		FAILED_HOST_RESOLVE,
		FAILED_SOCKET,
		FAILED_BIND,
		FAILED_LISTEN,
		FAILED_CONNECTION,
		FAILED_SELECT,
		FAILED_SEND,
		FAILED_RECV,
		ALREADY_CONNECTED,
		DISCONNECTED,
		TIMEOUT
	};

	static int CHECK ( );
	
	static int Start ( std::string name, std::string port );

	static int New_Connection ( );

    static int Connect ( std::string new_name, std::string address );

	static int Send ( const char* _buf, long size, std::string node );

	static int Recv ( char* _buf, long size, std::string node );

	static std::vector<std::string> Connected ( );

	static void End ( );
} /* Online */ } // ReKat

#endif