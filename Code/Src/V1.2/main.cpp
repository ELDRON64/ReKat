#include "node_treads.hpp"
#include "controlls.hpp"
#include "file_manager.hpp"

int main ( int argc, char const *argv[] ) {
    // login infos
    std::string name = "";
    std::string pass = "";
    int port = -1;
    
    switch ( argc ) {
    case 3: std::cout << "command defined name/pass\n"; name = argv[1]; pass = argv[2]; break;
    case 4: std::cout << "command defined name/pass\n"; name = argv[1]; pass = argv[2]; port = std::stoi(argv[3]); break;
    }

    // get infos from GUI
    // starting GRAPIK
    grapik::Start ( "ReKat Kave", SCR_WIDTH, SCR_HEIGHT, false, false, true );
    grapik::SetIcon ( "favicon.png" );

    Shader shader;
    shader.Make("Shaders/text.vs", "Shaders/text.fs");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    Text text;
    text.make ("death_record.ttf") << '\n';

    history.push_back ("");

    // info loop
    bool Infos_get = false;
    while ( grapik::IsEnd( ) && !Infos_get ) {
        // when a new command is added (\n pressed) get the last command as parameter        
        glClearColor(0.09412f, 0.5451f, 0.74118f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // command out;
        text.RenderText ( shader, output.str(), 25.0f, SCR_HEIGHT - 75.0f, 1.0f, glm::vec3(0.21875f, 0, 0.21875f), SCR_WIDTH - 50.0f, 50.0f, 8, 0 );

        // command box
        text.RenderText ( shader, "$ " + history[current_command], 25.0f, 100.0f, 0.75f, glm::vec3(0.3, 0.7f, 0.9f),SCR_WIDTH - 50.0f, 50.0f, 3, 0 );

        grapik::Pool();
        if ( name == "") {
            output.str("Login\nInsert name: "); if ( history.size() > 1 ) 
            { name = history [0]; }
        }
        else if ( pass == "" ) { 
            output.str("Login\nInsert password:"); if ( history.size() > 2 ) 
            { pass = history [1]; }
        }
        else if ( ! ( port == 0 || ( 1024 <= port && port <= 65535 )) ) {
            output.str("Node port\nInsert port: ( 0 for "+ std::to_string(DPORT) +" )"); if ( history.size() > 3 ) {
                // remover "$ "
                port = stoi ( history[2] );
                history.pop_back ();
                current_command--;
                Infos_get = true;
                if ( port == 0 ) { port = DPORT; }
            }
        } else {
            Infos_get = true;
        }
    }

    if ( Infos_get == false ) {
        std::cout << "cannot get infos\n";
        return online::FAILURE;
    }

    /*
    std::cout << "INFOS GET";
    std::cout << "\nname: " << name;
    std::cout << "\npass: " << pass;
    std::cout << "\nport: " << port << '\n';
    */
    output.str ("");
    history.clear ( );
    current_command = 0;

    Begin_string += name + '\n';
    output << Begin_string;

    // getting ID
    size_t ID;
    std::string path = setup ( name, pass, &ID );
    output << "path: " << path << "\nID: " << ID << '\n';

    history.push_back ( "" );
    
    // starting ONLINE
    long long start_result = online::Start ( name, 0, port ) << '\n';
    output << "start result: " << ( start_result == 0 ? "succes" : "failed: " + std::to_string ( start_result ) ) << '\n';

    // ONLINE threads
    std::thread conn_thread;
    conn_thread = std::thread ( Connections );

    std::thread recv_thread;
    recv_thread = std::thread ( Check_connections );

    // random bg color 
    srand ( (int)ID);
    float BGR = 0.5f + ((float)(rand()%256))/512.0f, BGG = 0.5f + ((float)(rand()%256))/512.0f, BGB = 0.5f + ((float)(rand()%256))/512.0f;

    // main loop
    int max_out_lines = 8;
    float line_heigth = 50.0f;

    int fps = 0;
    bool dis = true;
    int _time = time(0);
    while ( !Main_shutdown && grapik::IsEnd( ) ) {
        glClearColor(BGR, BGG, BGB, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        fps++;
        if ( _time < time (0) ) { _time = time (0); std::cout << "fps: " << fps << " time: " << _time << '\n'; fps = 0; dis = !dis; }

        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // --------------------------- top margin - input box
        max_out_lines = ( SCR_HEIGHT - 75.0f      - 100.0f )  /line_heigth;

        // command out;
        total_lines = total_lines <= max_out_lines ? 0 : total_lines - max_out_lines;
        total_lines  = text.RenderText ( shader, output.str(), 25.0f, SCR_HEIGHT - 75.0f, 1.0f, glm::vec3(1-BGG, 1-BGR, 1-BGB), SCR_WIDTH - 50.0f, line_heigth, max_out_lines, start_line - total_lines );

        // command box
        text.RenderText ( shader, "$ " + history[current_command] + ( dis ? '/' : '\\' ), 25.0f, 100.0f, 0.75f, glm::vec3(0.0, 0.0f, 0.0f),SCR_WIDTH - 50.0f, 50.0f, 3, 0 );

        grapik::Pool();
    }
    Main_shutdown = true;
    grapik::Terminate ( );

    dump_history (path);

    // terminate threads
    if ( recv_thread.joinable() ) { recv_thread.join ( ); }
    std::cout << "ended recive\n";

    if ( conn_thread.joinable() ) {
        TerminateThread ((HANDLE)conn_thread.native_handle(),1);
        conn_thread.detach ( );
    }
    std::cout << "--------------------------- END --------------------------\n";

    return SUCCESS;
}

// add the trasmition of N size string