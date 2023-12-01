#define OPENGL 
#define ALL_MODULES
#include <ReKat.hpp>

#include <iostream>

void foo ();

Button b ( "carlo", 100, 100, 100, 100, &foo );

void foo () 
{ std::cout << "ciao\n"; b.Y += 10; }

glm::vec2 pos = {300,400};

static void ReKat::grapik::Input::Keyboard ( GLFWwindow* window, int key, int scancode, int action, int mode ) {
    if ( ( action == GLFW_PRESS || action == GLFW_REPEAT ) ) {
        if ( key == GLFW_KEY_ESCAPE ) { grapik::End(); }
        if ( key == GLFW_KEY_W ) { pos += glm::vec2(-10,0); }
        if ( key == GLFW_KEY_A ) { pos += glm::vec2(0,-10); }
        if ( key == GLFW_KEY_S ) { pos += glm::vec2(10,0); }
        if ( key == GLFW_KEY_D ) { pos += glm::vec2(0,10); }
        b.X = pos.y;
        b.Y = pos.x;
    }
}
static void ReKat::grapik::Input::Mouse_pos ( GLFWwindow* window, double xpos, double ypos ) 
{ b.Update_mause ( xpos, ypos ); }
static void ReKat::grapik::Input::Mouse_key ( GLFWwindow* window, int button, int action, int mods ) 
{ if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) { b.Pressed ( ); } }
static void ReKat::grapik::Input::ScrollWell ( GLFWwindow* window, double xoffset, double yoffset ) { }
static void ReKat::grapik::Input::FreamBufferResize ( GLFWwindow* window, int width, int height ) { }
static void ReKat::grapik::Input::Caracters ( GLFWwindow* window, unsigned int codepoint ) { }

static int SCR_W = 800;
static int SCR_H = 600;

int main(int argc, char const *argv[]) {
    ReKat::grapik::Start( "button test", SCR_W, SCR_H );
    
    // load shaders
    Shader text;
    std::cout << "shader (text) make: " << text.Make( "Shaders/text.vs", "Shaders/text.fs" );
    Shader sprite;
    std::cout << "\nshader (sprite) make: " << sprite.Make( "Shaders/sprite.vs", "Shaders/sprite.fs" );

    // set shader params
    glm::mat4 projection = glm::ortho ( 0.0f, static_cast<float>(SCR_W), 0.0f, static_cast<float>(SCR_H) );
    text.Use();
    text.setMat4 ( "projection", projection );
    projection = glm::ortho ( 0.0f, static_cast<float>(SCR_W), static_cast<float>(SCR_H), 0.0f, -1.0f, 1.0f );
    sprite.Use();
    sprite.setInt ( "image", 0 );
    sprite.setMat4 ( "projection", projection );

    // load text
    Text t_render;
    std::cout << "\ntext make: " << t_render.Make( "death_record.ttf" );

    // load texture
    Texture texture;
    std::cout << "\ntexture make: " << texture.Make( "lebutton.png" );

    // create sprite
    Sprite s_render ( sprite );


    while ( ReKat::grapik::IsEnd( ) ) {
        glClearColor(0.5f, 0.6f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        text.Use();
        t_render.RenderText( text, "text", SCR_H, 25.0f, 100.0f, 0.75f, glm::vec3(0.0, 0.0f, 0.0f), 400.0f - 50.0f, 50.0f, 3, 0 );
        b.Draw ( t_render, text, s_render, texture, SCR_H );

        ReKat::grapik::Pool();
    }
    ReKat::grapik::Terminate ();

    return 0;
}
