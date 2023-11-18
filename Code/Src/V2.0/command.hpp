#include "global.hpp"

long long command ( std::string command ) {
    // tokenize
    // Vector of string to save tokens
    std::vector <std::string> tokens;
     
    // stringstream class check1
    std::stringstream check1(command);
    
    std::string intermediate;
     
    // Tokenizing w.r.t. space ' '
    while ( getline ( check1, intermediate, ' ' ) ) { tokens.push_back(intermediate); }

    // command set ---------------------
    // ---------------------------------
    if ( tokens.size( ) == 1 ) { return NO_COMMAND; }

    tokens.erase ( tokens.begin () );


    // args: name, ip, <port>
    if ( tokens[0] == "connect" ) {
        int p = -999;
        if ( tokens.size ( ) == 3 ) { p = online::Connect ( tokens[1], tokens[2] ); }
        if ( tokens.size ( ) == 4 ) { p = online::Connect ( tokens[1], tokens[2], tokens[3].c_str( ) ); }
        
        switch ( p ) {
            case -999: return FAULTY_COMMAND; break;
            case online::SUCCESS: output << "connected to: " << tokens[1] << '\n'; return SUCCESS;        
            default: return p; break;
        }
        
    }

    // args: node, msg
    if ( tokens[0] == "msg" ) {
        if ( tokens.size ( ) >= 3 ) {
            // check for multiple nodes
            std::vector < std::string > nodes;
            std::stringstream nodes_S (tokens[1]);
            // Tokenizing w.r.t. comma ','
            output << "stringstream: " << nodes_S.str();
            while ( getline ( nodes_S, intermediate, ',' ) ) { nodes.push_back(intermediate); output << "\nmsg node: " << intermediate; }
            output << "\nnodes" << nodes.size() << "\n ";// << nodes[0] << '\n';
            
            for ( auto node : nodes ) {
                // check if connected to node
                bool C = false;
                for ( std::string s : online::Connected ( ) ) { if ( s == node ) { C = true; } }
                if ( C == false ) { output << node << " is not connected\n"; }
                std::string R = "";
                for (size_t i = 2; i < tokens.size(); i++) { R += " " + tokens[i]; }
                R.erase (0,1);
                output << "to " << node << ": " << R << '\n';
                online::Send ( R.c_str(), R.size(), node ); 
            }
            return SUCCESS;
        }
        output << "command: " << command << " size: " << tokens.size() << '\n';
        return FAULTY_COMMAND;
    }

    if ( tokens[0] == "connected" ) {
        for ( auto s : online::Connected () ) 
        { output << "connected to: " << s << '\n'; } 
        if ( online::Connected().size() == 0 ) { output << "nobody there\n"; }
        return SUCCESS;
    }

    if ( tokens[0] == "clear" ) { output.str(""); output << Begin_string; return SUCCESS; }

    if ( tokens[0] == "refresh" ) { return online::Refresh(); }

    return INCORRECT_COMMAND;
}

void execute_command ( ) {
    if (history[current_command] == "$ exit") { Main_shutdown = true; }
    // output << '\n' << name << "@localhost: " << history[current_command] << '\n'; 
    int r = command ( history[current_command] );
    if ( r != 0 ) {
        switch ( r ) {
            case -1: output << "NO_COMMAND\n"; break;
            case -2: output << "FAULTY_COMMAND\n"; break;
            case -3: output << "INCORRECT_COMMAND\n"; break;
        }
    }
    current_command = history.size ( );
    if ( history[history.size()-1] == "$ " ) { current_command--; return; }
    history.push_back ("$ ");
}



// add the trasmition of N size string