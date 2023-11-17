#include "global.hpp"

void Connections ( ) { 
    while ( !Main_shutdown ) { 
        online::New_Connection();
    output << "Connected to: " << online::Connected()[online::Connected().size()-1] <<'\n';
} }

void Recive ( std::string node ) {
    int status;
    size_t size = 0;
    char *_buf; 
    while ( !Main_shutdown ) {
        _buf = online::Recv ( node, &status, &size, -1 );
        if ( status == online::FAILED_RECV ) 
        { output << "connection with " << node << " closed\n"; online::Close_sock (node); return; }
        output << "fr " + node + ": " + std::string(_buf) + '\n';
    }
}

void Check_connections ( ) {
    std::vector < std::thread > node_threads;
    std::vector < std::string > nodes = online::Connected();
    std::string node_name;
    while ( !Main_shutdown ) {
        if ( nodes == online::Connected() ) { continue; }
        nodes = online::Connected();
        // inizialize last n
        int N = nodes.size() - node_threads.size();
        for (int i = 0; i < N; i++) {
            node_name = nodes[nodes.size() - i - 1];
            node_threads.push_back ( std::thread ( Recive, node_name ) );
        }
    }

    // close nodes
    nodes = online::Connected();
    // for ( auto node : nodes ) { online::Close_sock ( node ); }

    // terminate nodes
    if ( node_threads.size() == 0 ) { return; }
    for ( size_t i = 0; i < node_threads.size() - 1; i++ ) 
    {   if (node_threads[i].joinable()) 
        { TerminateThread ( (HANDLE)node_threads[i].native_handle(), 1 ); node_threads[i].detach();} }

    output << "local nodes terminated\n";
}