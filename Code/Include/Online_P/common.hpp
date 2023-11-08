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
	#define DTIMEOUT 5

	#define NAME_LEN 32
	
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
		TIMEOUT,
		NOBODY_THERE
	};

	static int CHECK ( );
	
	// start a node with name and id with optional port
	static int Start ( std::string name, size_t id, const char* port = DPORT_W );

	static int New_Connection ( );

    static int Connect ( char* new_name, std::string address, const char * port = DPORT_W );

	static int Send ( const char* _buf, long size, char* node );

	static int Recv ( char* _buf, long size, char* node );

	static int Recv_all ( char* _buf, long size );

	static std::vector<char*> Connected ( );

	static void End ( );

	char* Format_String ( std::string string );
} /* Online */ } // ReKat

#endif