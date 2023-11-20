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
    
    Shader shader;
    shader.Make("Shaders/text.vs", "Shaders/text.fs");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(400), 0.0f, static_cast<float>(500));
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    Text text;
    text.make ("death_record.ttf") << '\n';

    while ( IsEnd() ) {
        glClearColor(0.5f, 0.6f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        b.Draw ( text, shader );

        Pool();
    }
    

    return 0;
}
