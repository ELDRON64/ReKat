#include "global.hpp"

void Connections ( ) { 
    while ( !Main_shutdown ) { 
        online::New_Connection();
        output << "Connected to: " << online::Connected()[online::Connected().size()-1] <<'\n';
    }
    std::cout << "stop getting connections\n";
}

void Recive ( std::string node, bool * is_closed ) {
    int status;
    size_t size = 0;
    char *_buf; 
    while ( !Main_shutdown ) {
        _buf = online::Recv ( node, &status, &size, -1 );
        if ( status == online::FAILED_RECV ) 
        { output << "connection with " << node << " closed\n"; online::Close_sock (node); break; }
        output << "fr " + node + ": " + std::string(_buf) + '\n';
    }
    std::cout << "closed recvie with" << node << '\n';
    *is_closed = true;
    return;
}

void Check_connections ( ) {
    // store threads and their state
    std::vector < std::pair < std::pair < bool*, std::string > , std::thread > > threads;
    while ( !Main_shutdown ) {
        // if a new connection starts add its thread and status
        std::vector < std::string > missing;
        for ( auto s : online::Connected() ) {
            bool found = false;
            for (size_t i = 0; i < threads.size(); i++) { 
                if ( s == threads[i].first.second && *threads[i].first.first == true ) 
                    { found = true; } }
            found == true ? 0 : missing.push_back (s);
        }

        for ( auto m : missing ) 
        // start missing threads 
        { std::cout << "adding " << m << '\n'; bool end = false; 
        threads.push_back ( std::make_pair ( std::make_pair ( &end, m ), std::thread ( Recive, m, &end ) ) ); }
    }

    // close nodes
    for ( size_t i = 0; i < threads.size(); i++ ) { if ( *threads[i].first.first ) { online::Close_sock ( threads[i].first.second ); } }

    // terminate nodes
    if ( threads.size() == 0 ) { return; }

    for ( size_t i = 0; i < threads.size(); i++ ) {   
        if ( threads[i].second.joinable() ) { 
            TerminateThread ( (HANDLE)threads[i].second.native_handle(), 1 ); 
            threads[i].second.detach(); } }

    output << "local nodes terminated\n";
}