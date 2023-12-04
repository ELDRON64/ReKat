#define OPENGL
#define ALL_MODULES
#include <ReKat.hpp>
#include <thread>
#include <chrono>
using namespace ReKat;

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
Camera cam ({0,0},{SCR_WIDTH, SCR_HEIGHT});

static void grapik::Input::Keyboard ( GLFWwindow* window, int key, int scancode, int action, int mode ) { }
bool press = false;
double m_x,m_y;

static void grapik::Input::Mouse_pos ( GLFWwindow* window, double xposIn, double yposIn ) { 
    if ( press ) {
        cam.DMove ( {(m_x - xposIn) * cam.GetScale(),  (m_y - yposIn) * cam.GetScale()}  );
    }
    m_x = xposIn;
    m_y = yposIn;
}
static void grapik::Input::Mouse_key ( GLFWwindow *window, int button, int action, int mods ) {
    if ( button == GLFW_MOUSE_BUTTON_LEFT ) {
        if ( action == GLFW_PRESS ) { press = true; }
        if ( action == GLFW_RELEASE ) {press = false;}
    }
}
static void grapik::Input::ScrollWell ( GLFWwindow* window, double xoffset, double yoffset ) {
    cam.DScale(-yoffset*0.1f);
}
static void grapik::Input::FreamBufferResize ( GLFWwindow* window, int width, int height ) {
    glViewport ( 0, 0, SCR_WIDTH = width, SCR_HEIGHT = height );
    cam.Resize({width,height});
}
static void grapik::Input::Caracters ( GLFWwindow* window, unsigned int codepoint ) { }

int main(int argc, char const *argv[]) {
    grapik::Start ( "ReKat Kave", SCR_WIDTH, SCR_HEIGHT, false, false, true );
    grapik::SetIcon ( "favicon.png" );

    Shader sprite;
    std::cout << "sprite make: " << sprite.Make("Shaders/sprite_animation.vs", "Shaders/sprite_animation.fs");
    Shader tilemap_shader;
    std::cout << "\ntilemap_shader make: " << tilemap_shader.Make("Shaders/sprite_animation.vs", "Shaders/sprite_animation.fs");
    Texture tileset;
    std::cout << "\ntileset make: " << tileset.Make ( "Data/tile1.png" );
    Texture _sprite;
    std::cout << "\nsprite make: " << _sprite.Make ( "Data/sprite4.png" );

    glm::mat4 projection = glm::ortho ( 0.0f, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f );
    sprite.setInt ( "image", 0 );
    sprite.setMat4 ( "projection", cam.GetWiew() );
    tilemap_shader.setInt ( "image", 0 );
    tilemap_shader.setMat4 ( "projection", projection );

    Sprite renderer ( sprite );
    renderer.Set_Texture ( _sprite,{2,2});

    Sprite t_renderer ( tilemap_shader );
    t_renderer.Set_Texture ( tileset,{32,32} );

    Tilemap tilemap ( t_renderer, {32,32} );
    std::cout << "\ntilemap make: " << tilemap.Make( "Data/Tilemaps/Layer2.csv" );

    // main loop
    int frame = 0;
    int fps = 0;
    int _time = time(0);
    float scale = 1.0f;
    while ( grapik::IsEnd( ) ) {
        glClearColor(1, 1, 1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        fps++;
        if ( _time < time (0) ) { _time = time (0); std::cout << "\nfps: " << fps << " time: " << _time; fps = 0; }
        if ( fps%20 == 0 ) { frame ++; }

        tilemap.Draw({100,300},{50,50});
        tilemap_shader.setMat4 ( "projection", cam.GetWiew() );
        renderer.Draw_frame( frame, {300,100},{100,100},0 );
        sprite.setMat4 ( "projection", cam.GetWiew() );

        grapik::Pool();
    }
    grapik::Terminate ( );

    std::cout << "\n--------------------------- END --------------------------\n";

    return 0;
}
