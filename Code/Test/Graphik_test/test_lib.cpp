#include <ReKat.hpp>
using namespace ReKat;
using namespace ReKat::grapik;

static void Input::Keyboard ( GLFWwindow* window, int key, int scancode, int action, int mode ) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
int main ( ) {
    Start( );

}