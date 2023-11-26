#define OPENGL
#include <ReKat.hpp>
using namespace ReKat::grapik;

void foo () {
    std::cout << "ciao\n";
}

Gui::Button b("carlo", 100, 100, 100, 100, &foo );

static void ReKat::grapik::Input::Keyboard ( GLFWwindow* window, int key, int scancode, int action, int mode ) { }
static void ReKat::grapik::Input::Mouse ( GLFWwindow* window, double xpos, double ypos ) 
{ b.Update_mause ( xpos, ypos ); }
static void ReKat::grapik::Input::ScrollWell ( GLFWwindow* window, double xoffset, double yoffset ) { }
static void ReKat::grapik::Input::FreamBufferResize ( GLFWwindow* window, int width, int height ) { }
static void ReKat::grapik::Input::Caracters ( GLFWwindow* window, unsigned int codepoint ) { }


int main(int argc, char const *argv[]) {
    Start( "button test", 400, 500 );
    
    // load shaders
    std::cout << "text shader load: " << Resource_Manager::Load_Shader ( "text", "Shaders/text.vs", "Shaders/text.fs" ) << '\n';

    // set shader params
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(400), 0.0f, static_cast<float>(500));

    Resource_Manager::Get_Shader ( "text" ).setMat4 ( "projection", projection );

    // load text
    std::cout << "text load: " << Resource_Manager::Load_Text ( "record", "death_record.ttf" ) << '\n';

    while ( IsEnd() ) {
        glClearColor(0.5f, 0.6f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Resource_Manager::Get_Text ( "record" ).RenderText( Resource_Manager::Get_Shader ( "text" ), "text", 25.0f, 100.0f, 0.75f, glm::vec3(0.0, 0.0f, 0.0f), 400.0f - 50.0f, 50.0f, 3, 0 );

        b.Draw ( Resource_Manager::Get_Text ( "record" ), Resource_Manager::Get_Shader ( "text" ) );

        Pool();
    }
    

    return 0;
}
