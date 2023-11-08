#ifndef KAT_ONLINE
#define KAT_ONLINE

// network
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

// Common
#include "common.hpp"

namespace ReKat {
namespace online {
	namespace internal {
        struct node_infos {
            SOCKET sock = INVALID_SOCKET;
            char* internal_name;
            size_t internal_id;
        };

        node_infos this_node;

        std::unordered_map < char* , node_infos > node_network;

        static WSADATA wsaData;
		
        static int send_buf ( node_infos sock, const char *buf, size_t sizeof_buf, timeval * wait_time );
		static int recv_buf ( node_infos sock, char *buf, size_t sizeof_buf, timeval * wait_time );
	} // private variables
} /* Online */ } // ReKat

int ReKat::online::Start 
( std::string name, size_t id, const char* port ) {
    internal::this_node.internal_name = Format_String (name);

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &internal::wsaData) != 0) 
    { return FAILED_WSADATA; }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    if ( getaddrinfo(NULL, port, &hints, &result) != 0 ) 
    { WSACleanup(); return FAILED_HOST_RESOLVE; }

    // Create a SOCKET for the server to listen for client connections.
    internal::this_node.sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if ( internal::this_node.sock == INVALID_SOCKET ) {
        // printf("socket failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return FAILED_SOCKET;
    }

    // Setup the TCP listening socket
    if ( bind( internal::this_node.sock, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR ) {
        // printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(internal::this_node.sock);
        WSACleanup();
        return FAILED_BIND;
    }

    freeaddrinfo(result);

    // start lisening
    if ( listen( internal::this_node.sock, SOMAXCONN ) == SOCKET_ERROR ) {
        // printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(  internal::this_node.sock );
        WSACleanup();
        return FAILED_LISTEN;
    }

    return SUCCESS;
}

static int ReKat::online::Connect 
( char * new_name, std::string address, const char * port ) {
    internal::node_infos new_node;

    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    int erroe;
    if ( erroe = getaddrinfo(address.c_str(), port, &hints, &result) != 0 ) 
    { std::cout << "erroe: "<< WSAGetLastError() << '\n'; return FAILED_HOST_RESOLVE; }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) 
        { return FAILED_SOCKET; }

        // Connect to server.
        if (connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen) == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) 
    { closesocket(ConnectSocket); return FAILED_CONNECTION; }

    new_node.sock = ConnectSocket;
    new_node.internal_name = new_name;

    // sending name
    if ( internal::send_buf ( new_node, internal::this_node.internal_name, NAME_LEN, nullptr) == FAILED_SEND ) 
    { closesocket(ConnectSocket); return FAILED_SEND; }

    // sending id
    if ( internal::send_buf ( new_node, (char*)&internal::this_node.internal_id, sizeof(size_t), nullptr) == FAILED_SEND ) 
    { closesocket(ConnectSocket); return FAILED_SEND; }

    internal::node_network.insert( {new_name, new_node} );

	return SUCCESS;
}

static int ReKat::online::Send 
( const char* _buf, long size, char* node ) {
	auto Timeout = timeval();
	Timeout.tv_sec = DTIMEOUT;
	return internal::send_buf ( internal::node_network[node], _buf, size, &Timeout );
}

static int ReKat::online::Recv 
( char* _buf, long size, char* node ) {
	auto Timeout = timeval();
	Timeout.tv_sec = DTIMEOUT;
	return internal::recv_buf ( internal::node_network[node], _buf, size, &Timeout );
}

static int ReKat::online::New_Connection 
( ) {
	fd_set FD_Listen;
	FD_ZERO ( &FD_Listen ); //Clearing the socket set
	FD_SET  ( internal::this_node.sock, &FD_Listen ); //Adding the master socket to the set 

	//Waiting for something to happen on the master socket.
	int act = select( internal::this_node.sock + 1 , &FD_Listen , nullptr , nullptr , nullptr );

	if ((act < 0) && (errno!=EINTR)) { return FAILED_SELECT; }

	//Any activity on the master socket is treated as an incoming connection
	if ( FD_ISSET( internal::this_node.sock, &FD_Listen ) ) {
        internal::node_infos new_node;
        
        // Accept a client socket
		new_node.sock = accept( internal::this_node.sock, NULL, NULL );

        if ( new_node.sock == INVALID_SOCKET ) 
        { return FAILED_CONNECTION; }

        // read name
        if (internal::recv_buf (new_node, (char*)&new_node.internal_name, NAME_LEN, nullptr) == FAILED_RECV) 
        { closesocket(new_node.sock); return FAILED_CONNECTION; }
        
        // read id
        if ( internal::send_buf ( new_node, (char*)&new_node.internal_id, sizeof(size_t), nullptr) == FAILED_SEND ) 
        { closesocket(new_node.sock); return FAILED_CONNECTION; }

	    internal::node_network.insert( { new_node.internal_name, new_node } );
	}

    return SUCCESS;
}

static int ReKat::online::internal::send_buf 
( node_infos sock, const char *buf, size_t sizeof_buf, timeval *wait_time ) {
	fd_set sending_sock;
	FD_ZERO(&sending_sock);
	FD_SET(sock.sock, &sending_sock);
		
	int act = select(sock.sock + 1, nullptr, &sending_sock ,nullptr, wait_time);

	if (act < 0) { return TIMEOUT; }
	if (FD_ISSET(sock.sock, &sending_sock)) {
		long remaining = sizeof_buf;
		long result = 0;
		long sent = 0;

		while (remaining > 0) {
			result = send(sock.sock, buf+sent, remaining, 0);

			if (result > 0) { 
				remaining -= result; sent += remaining; 
			}
			else if (result < 0) { std::cout << "\tsend errno: " << errno << '\n'; return FAILED_SEND; }
		}
				
		return SUCCESS;
	}

	return FAILED_SEND;
}

static int ReKat::online::internal::recv_buf 
( node_infos sock, char *buf, size_t sizeof_buf, timeval * wait_time ) {
	fd_set recive_sock;
	FD_ZERO(&recive_sock);
	FD_SET(sock.sock, &recive_sock);
			
	int act = select(sock.sock + 1, &recive_sock, nullptr ,nullptr, wait_time);

	if (act < 0) { return TIMEOUT; }
	if (FD_ISSET(sock.sock, &recive_sock)) {
		long remaining = sizeof_buf;
		long received = 0;
		long result = 0;
		
		while (remaining > 0) {
			result = recv(sock.sock, buf+received, remaining, 0);
			if (result > 0) {
				remaining -= result;
				received += result;
			}
			else if (result == 0) { return DISCONNECTED; /*disconnection*/ }
			else if (result  < 0) { std::cout << "\trecv errno: " << errno << '\n'; return FAILED_RECV; }
		}

		return SUCCESS;
	}

	return FAILED_RECV;
}

static int ReKat::online::Recv_all 
( char* _buf, long size ) {
    if ( internal::node_network.size() == 0 ) { return NOBODY_THERE; }

	fd_set recive_sockets;
	FD_ZERO ( &recive_sockets );
    // add all sockets
    SOCKET max = 0;
    for ( auto sock : internal::node_network ) { 
        if ( sock.second.sock > max ) { max = sock.second.sock; }
        FD_SET( sock.second.sock, &recive_sockets ); 
    }
	
    timeval wait_time = timeval();
    wait_time.tv_sec = DTIMEOUT;
	int act = select( max + 1, &recive_sockets, nullptr ,nullptr, &wait_time);

	if (act < 0) { return TIMEOUT; }
    // check every socket // the first pending get to read
    for ( auto sock : internal::node_network ) {
    if ( FD_ISSET ( sock.second.sock, &recive_sockets ) ) 
    { return Recv ( _buf, size, sock.first ); } }

	return FAILED_RECV;
}

static void ReKat::online::End 
( ) {
    // stop listeing
    closesocket ( internal::this_node.sock );

    // close sockets
    for ( auto sock : internal::node_network ) 
    { closesocket ( sock.second.sock ); }

	WSACleanup();
}

static std::vector<char*> ReKat::online::Connected 
( ) {
    std::vector<char*> nodi;
    for ( auto node : internal::node_network ) { nodi.push_back(node.first); }
    return nodi;
}

static int ReKat::online::CHECK 
( ) { 
    internal::node_infos p;
    p.sock = INVALID_SOCKET;
    std::cout << &p << '\n';
    std::cout << p.sock << '\n'; 
    
std::cout << "check valid"; return 2; }

char* ReKat::online::Format_String ( std::string string ) {
    char* char_s = (char*) calloc (NAME_LEN, sizeof(char));

    for (size_t i = 0; i < string.size() && i < NAME_LEN; i++) 
    { char_s[i] = string[i]; }

    return char_s;
}

#endif