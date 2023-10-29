#include <iostream>
#include <ReKat.hpp>

int client ( ) {
	std::cout << "start\n";
	const char* _buf = "testicular cancer";
	std::cout << "Connection result: " << ReKat::online::Connect ( "main" ) <<'\n';
	int s = ReKat::online::Send ( _buf, 18 );
	std::cout << "Send result: " << s  <<'\n';
	ReKat::online::End ( );
	return 0;
}

int server ( ) {
	int node_sock;
	sockaddr_in node_adr;
		
	std::cout << "starting socket\n";

	node_adr.sin_family = AF_INET;
	node_adr.sin_addr.s_addr = INADDR_ANY;
	node_adr.sin_port = htons( 42069 );

	if( (node_sock = socket ( AF_INET , SOCK_STREAM , 0 ) ) < 0) {
		std::cout << "FAILED_SOCKET\n";
		return -1;
	}

	if ( bind ( node_sock, (struct sockaddr *)&node_adr, sizeof(node_adr) ) < 0 ) {
		std::cout << "FAILED_BIND\n";
		return -1;
	}

	if ( listen ( node_sock, 3 ) < 0 ) {
		std::cout << "LISTENING_ERROR";
		return -1;
	}

	std::cout << "set up node socket\n\n";

	sockaddr_in new_adr;
	int new_sock;
	int new_adrlen = sizeof(new_adr);

	if ( ( new_sock = accept( node_sock, (struct sockaddr*)&new_adr,(socklen_t*)&new_adrlen ) ) < 0 ) {    
		std::cout << "ERRORE_DURING_ACCEPTING_CONNCETION" << std::endl;
		return -1;
	}

	std::cout << "node conected\n";
	std::cout << "node with ip: " << inet_ntoa ( new_adr.sin_addr ) << std::endl;
	std::cout << "node on port: " << ntohs( new_adr.sin_port ) << "\n\n";

	// sending public server
	// reciving public node

	char _buf[18];
	auto Timeout = timeval();
	Timeout.tv_sec = 1;
	int r = ReKat::online::internal::recv_buf ( new_sock, _buf, 18, &Timeout);
	std::cout << "recv r: " << r << '\n';

	std::cout << _buf << '\n';
	close ( new_sock );
	close ( node_sock );
	return 0;
}

int main ( int argc, char const *argv[] ) {
	if ( argc != 2 ) { std::cout << "no service"; return 0; }
	switch 
	( argv[1][0] ) {
		case 'c': client(); break;
		case 's': server(); break;
		default: std::cout << "no service"; break;
	}
	return 0;
}