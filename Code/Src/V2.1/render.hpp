#include "controlls.hpp"

void button_callback ( ) {
    grapik::End();
}

// Initilalize renderer
void Grapik_Init ( ) {
    // start window
    ReKat::grapik::Start ( "Kat Kave", SCR_WIDTH, SCR_HEIGHT, false, false, true );
    std::cout << "icon set: " << ReKat::grapik::SetIcon ( "favicon.png" ) << '\n';

    // Load resources
    std::cout << "text shader make: "    << Manager::Shader_Load ( "text", "Shaders/text.vs", "Shaders/text.fs" ) << '\n';
    std::cout << "sprite shader make: "  << Manager::Shader_Load ( "sprite",  "Shaders/sprite_animation.vs", "Shaders/sprite_animation.fs" ) << '\n';
    std::cout << "empty_sprite shader make: "  << Manager::Shader_Load ( "empty_sprite",  "Shaders/sprite_animation.vs", "Shaders/sprite_animation.fs" ) << '\n';
    std::cout << "tilemap shader make: " << Manager::Shader_Load ( "tilemap", "Shaders/sprite_animation.vs", "Shaders/sprite_animation.fs" ) << '\n';
    std::cout << "UI shader make: " << Manager::Shader_Load ( "UI", "Shaders/sprite_animation.vs", "Shaders/sprite_animation.fs" ) << '\n';
    

    std::cout << "sprite texture make: "  << Manager::Texture_Load ( "sprite", "Sprites/soldato.png" ) << '\n';
    std::cout << "Button texture make: "  << Manager::Texture_Load ( "Buttons", "Sprites/UI_menu.png" ) << '\n';
    std::cout << "empty_sprite texture make: "  << Manager::Texture_Load ( "empty_sprite", "Data/empty.png" ) << '\n';
    std::cout << "tileset texture make: " << Manager::Texture_Load ( "tileset", "Data/tile1.png" )  << '\n';
    
    std::cout << "death_record text make: " << Manager::Text_Load ( "death_record", "death_record.ttf", "text" ) << '\n';

    // configure resources
    Manager::Shader_Get("text")->setMat4("projection", glm::ortho ( 0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT) ));
    Manager::Shader_Get("sprite")->setInt ("image", 0);
    Manager::Shader_Get("sprite")->setMat4("projection", cam.GetWiew());
    Manager::Shader_Get("UI")->setInt ("image", 0);
    Manager::Shader_Get("UI")->setMat4("projection", cam.GetWiew());
    Manager::Shader_Get("empty_sprite")->setInt ("image", 0);
    Manager::Shader_Get("empty_sprite")->setMat4("projection", cam.GetWiew());
    Manager::Shader_Get("tilemap")->setInt ("image", 0 );
    Manager::Shader_Get("tilemap")->setMat4("projection", cam.GetWiew());

    // configure renderers
    Manager::Sprite_Load ( "sprite", "sprite", "sprite", {1,1} );
    Manager::Sprite_Load ( "UI", "UI", "Buttons", {3,4} );
    Manager::Sprite_Load ( "empty_sprite", "empty_sprite", "empty_sprite" );
    Manager::Sprite_Load ( "tilemap", "tilemap", "tileset", {32,32} );
    Manager::Tilemap_Load ( "tilemap", "tilemap", "Data/Tilemaps/Layer2.csv" );

    // configure objects
    Manager::Buttton_Load ( "start", "START", "UI", {0,0}, {100,100}, button_callback, 6 );

    // configure player
    Objects.insert( { "", Object ( Manager::Sprite_Get( "sprite" ), {100,100}, {100,100} )} );
}

uint64_t spash_start = Get_Time();
float duration = 5000.0f;
int Render_splash ( ) {
    float alpha = ( Get_Time() - spash_start ) / duration;
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    Manager::Shader_Get("text")->setMat4("projection", glm::ortho ( 0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT) ));

    Manager::Text_Get ( "death_record" )->RenderText ( "made with", {SCR_WIDTH/2 - 250, SCR_HEIGHT/2 + 100 },
                                                            {SCR_WIDTH-50.0f,200.0f}, 1.0f, glm::vec4(1.0, 1.0f, 1.0f,alpha));

    Manager::Text_Get ( "death_record" )->RenderText ( "Real Engine 5", {SCR_WIDTH/2 - 250, SCR_HEIGHT/2 },
                                                            {SCR_WIDTH-50.0f,200.0f}, 2.0f, glm::vec4(violet_fl,alpha));

    if ( alpha > 1 ) { return 1; } 
    else { return 0;}
}

float duration_2 = 500.0f;
int Render_splash_fade ( ) {
    float alpha = ( duration_2 - ( Get_Time() - spash_start ) ) / duration_2;
    Manager::Shader_Get("text")->setMat4("projection", glm::ortho ( 0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT) ));

    Manager::Sprite_Get ( "empty_sprite" )->Draw_frame( 0, {0, 0}, {SCR_WIDTH,SCR_HEIGHT}, 0, glm::vec4{0.0f,0.0f,0.0f,alpha} );

    Manager::Text_Get ( "death_record" )->RenderText ( "made with", {SCR_WIDTH/2 - 250, SCR_HEIGHT/2 + 100 },
                                                            {SCR_WIDTH-50.0f,200.0f}, 1.0f, glm::vec4(1.0, 1.0f, 1.0f,alpha));

    Manager::Text_Get ( "death_record" )->RenderText ( "Real Engine 5", {SCR_WIDTH/2 - 250, SCR_HEIGHT/2 },
                                                            {SCR_WIDTH-50.0f,200.0f}, 2.0f, glm::vec4(violet_fl,alpha));
    if ( alpha < 0 ) { std::cout << "end"; return 1; }
    else { return 0;} 
}

// Draws a new frame
int frame = 0;
int fps = 0;
int _time = time(0);
float scale = 1.0f;
bool dis = true;
int scrool = 0;
int old_out = 0;
float text_alpha = 0.5f;
void Render_text ( ) {
    // command out; 
    if ( text_mode ) { text_alpha = 1.0f; } else { text_alpha = 0.5; }
    int out = Manager::Text_Get ( "death_record" )->RenderText ( output.str(), {25.0f,SCR_HEIGHT-75.0f}, { SCR_WIDTH-50.0f, SCR_HEIGHT - 75.0f - 100.0f}, 1.0f, 
                                  glm::vec4(1-BGG, 1-BGR, 1-BGB,text_alpha), scrool );
    int max_rows = Manager::Text_Get ( "death_record" )->Get_Max_Rows ( SCR_HEIGHT-75.0f - 100.0f,1.0f );

    scrool = ( out >= max_rows ? out - max_rows : 0 );

    if ( old_out == out ) { scrool += start_line;
    } else { start_line = 0; }
    if ( scrool < 0 ) // lower limit
    { scrool = 0; start_line = old_start_line; }
    if ( scrool > out ) // upper limit
    { scrool = out; start_line = out;}
    old_out = out;

    if ( text_mode ) {
        // command box
        Manager::Text_Get ( "death_record" )->RenderText ( "$ " + history[current_command] + ( dis ? '/' : '\\' ), {25.0f,100.0f},
                                                            {SCR_WIDTH-50.0f,200.0f}, 0.75f, glm::vec4(0.0, 0.0f, 0.0f,text_alpha));
    }
}

void Render ( ) {
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if ( !text_mode ) { Render_text(); }

    fps++;
    if ( _time < time (0) ) { _time = time (0); std::cout << "\nfps: " << fps << " time: " << _time; fps = 0; dis = !dis; }
    if ( fps%20 == 0 ) { frame ++; }

    // updating camera projections
    Manager::Shader_Get( "sprite"  )->setMat4("projection", cam.GetWiew());
    Manager::Shader_Get( "tilemap" )->setMat4("projection", cam.GetWiew());
    Manager::Shader_Get("text")->setMat4("projection", glm::ortho ( 0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT) ));
    

    // Manager::Sprite_Get( "sprite" )->Draw_frame( frame, {300,100},{100,100},0 );
    // Manager::Text_Get ( "death_record" )->RenderText ( "ciao", {25.0f,SCR_HEIGHT-75.0f}, { SCR_WIDTH-50.0f, 200.0f}, 1.0f, glm::vec3(0.21875f, 0, 0.21875f));
    Manager::Tilemap_Get ( "tilemap" )->Draw({100,300},{50,50});

    for ( auto obj : Objects ) 
    { obj.second.Draw ( ); }

    /// ------------------------------------------------------------------------- ///
    // -------------------------------------- UI --------------------------------- //
    /// ------------------------------------------------------------------------- ///
    
    if ( text_mode ) { Render_text(); }

    Manager::Draw();
}
