#include <iostream>
#include <ReKat.hpp>
using namespace ReKat::grapik;

static void ReKat::grapik::Input::Keyboard ( GLFWwindow* window, int key, int scancode, int action, int mode ) { ReKat::grapik::End(); }
static void ReKat::grapik::Input::Mouse ( GLFWwindow* window, double xpos, double ypos ) { }
static void ReKat::grapik::Input::ScrollWell ( GLFWwindow* window, double xoffset, double yoffset ) { }
static void ReKat::grapik::Input::FreamBufferResize ( GLFWwindow* window, int width, int height ) { }

int main ( ) 
{ 
    Start ( "cok departement ", 1000, 1000 );
    while ( IsEnd( ) ) {
        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Pool( );
    }
    std::cout << "Hello world"; 
}