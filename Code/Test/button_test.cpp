#define OPENGL
#include <Graphik/button.hpp>
using namespace ReKat::grapik;

void foo () {
    std::cout << "ciao\n";
}

button b("carlo", 100, 100, 100, 100, &foo );

static void ReKat::grapik::Input::Keyboard ( GLFWwindow* window, int key, int scancode, int action, int mode ) { }
static void ReKat::grapik::Input::Mouse ( GLFWwindow* window, double xpos, double ypos ) 
{ b.Update_mause ( xpos, ypos ); }
static void ReKat::grapik::Input::ScrollWell ( GLFWwindow* window, double xoffset, double yoffset ) { }
static void ReKat::grapik::Input::FreamBufferResize ( GLFWwindow* window, int width, int height ) { }
static void ReKat::grapik::Input::Caracters ( GLFWwindow* window, unsigned int codepoint ) { }


int main(int argc, char const *argv[]) {
    Start( "button test", 400, 500 );
    
    // load shaders
    Shader text_shader;
    text_shader.Make ( "Shaders/text.vs", "Shaders/text.fs" );
    Shader sprite_shader;
    sprite_shader.Make ( "Shaders/sprite.vs", "Shaders/sprite.fs" );

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(400), 0.0f, static_cast<float>(500));

    text_shader.use ( );
    text_shader.setMat4 ( "projection", projection );

    sprite_shader.use ( );
    sprite_shader.setInt ( "image",0 );
    sprite_shader.setMat4 ( "projection", projection );

    // load text 
    Text text;
    text.make ("death_record.ttf") << '\n';

    // load texture
    Texture2D texture;
    // ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");

    // load sprite rendere
    Sprite sprite ( sprite_shader );

    while ( IsEnd() ) {
        glClearColor(0.5f, 0.6f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        b.Draw ( text, text_shader ,sprite, texture );

        Pool();
    }
    

    return 0;
}
