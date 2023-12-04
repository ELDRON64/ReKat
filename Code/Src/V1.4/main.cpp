#include "node_treads.hpp"
#include "controlls.hpp"
#include "file_manager.hpp"

int main ( int argc, char const *argv[] ) {
    grapik::Start ( "ReKat Kave", SCR_WIDTH, SCR_HEIGHT, false, false, true );
    grapik::SetIcon ( "favicon.png" );

    Shader sprite;
    std::cout << "sprite make: " << sprite.Make("Shaders/sprite_animation.vs", "Shaders/sprite_animation.fs");
    glm::mat4 projection = glm::ortho ( 0.0f, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f );
    sprite.Use();
    sprite.setInt ( "image", 0 );
    sprite.setMat4 ( "projection", projection );

    Texture texture;
    std::cout << "\ntexture make: " << texture.Make ( "Data/sprite3.png" );

    Sprite renderer ( sprite );
    renderer.Set_Texture(texture,{3,2});

    // main loop
    int frame = 0;
    int fps = 0;
    int _time = time(0);
    while ( !Main_shutdown && grapik::IsEnd( ) ) {
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        fps++;
        if ( _time < time (0) ) { _time = time (0); std::cout << "\nfps: " << fps << " time: " << _time; fps = 0; }
        if ( fps == 0 ) { frame ++; }

        renderer.Draw( texture, {100,100},{100,100},0,{1,1,1} );
        renderer.Draw_frame( frame, {300,100},{100,100},0,{1,1,1} );

        grapik::Pool();
    }
    Main_shutdown = true;
    grapik::Terminate ( );

    std::cout << "--------------------------- END --------------------------\n";

    return SUCCESS;
}

// add the trasmition of N size string