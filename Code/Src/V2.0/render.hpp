#include "controlls.hpp"

// Initilalize renderer
void Init ( ) {
    // start window
    grapik::Start ( "Kat Kave", SCR_WIDTH, SCR_HEIGHT );
    std::cout << "icon set: " << grapik::SetIcon ( "favicon.png" ) << '\n';

    // Load resources
    std::cout << "text shader make: "    << Manager::Shader_Load ( "text", "Shaders/text.vs", "Shaders/text.fs" ) << '\n';
    std::cout << "sprite shader make: "  << Manager::Shader_Load ( "sprite",  "Shaders/sprite_animation.vs", "Shaders/sprite_animation.fs" ) << '\n';
    std::cout << "tilemap shader make: " << Manager::Shader_Load ( "tilemap", "Shaders/sprite_animation.vs", "Shaders/sprite_animation.fs" ) << '\n';
    std::cout << "sprite texture make: "  << Manager::Texture_Load ( "sprite", "Data/sprite3.png" ) << '\n';
    std::cout << "tileset texture make: " << Manager::Texture_Load ( "tileset", "Data/tile1.png" )  << '\n';
    std::cout << "death_record text make: " << Manager::Text_Load ( "death_record", "death_record.ttf", "text" ) << '\n';

    // configure resources
    Manager::Shader_Get("text").setMat4("projection", glm::ortho ( 0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT) ));
    Manager::Shader_Get("sprite").setInt ("image", 0);
    Manager::Shader_Get("sprite").setMat4("projection", cam.GetWiew());
    Manager::Shader_Get("tilemap").setInt ("image", 0 );
    Manager::Shader_Get("tilemap").setMat4("projection", cam.GetWiew());

    // configure renderers
    Manager::Sprite_Load ( "sprite", "sprite", "sprite", {2,2} );
}

// Draws a new frame
void Render ( ) {
    glClearColor(1, 1, 1, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    Manager::Shader_Get( "sprite" ).Use();
    Manager::Sprite_Get( "sprite" ).Draw_frame( 0, {300,100},{100,100},0 );
    Manager::Text_Get ( "death_record" ).RenderText ( "ciao", {25.0f,SCR_HEIGHT-75.0f}, { SCR_WIDTH-50.0f, 200.0f}, 1.0f, glm::vec3(0.21875f, 0, 0.21875f));

    grapik::Pool();
}