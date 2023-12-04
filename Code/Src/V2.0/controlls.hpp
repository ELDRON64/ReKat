#define OPENGL
#define ALL_MODULES
#include <ReKat.hpp>
using namespace ReKat;

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
Camera cam ({0,0},{SCR_WIDTH, SCR_HEIGHT});

static void grapik::Input::Keyboard ( GLFWwindow* window, int key, int scancode, int action, int mode ) { }
static void grapik::Input::Mouse_pos ( GLFWwindow* window, double xposIn, double yposIn ) { }
static void grapik::Input::Mouse_key ( GLFWwindow *window, int button, int action, int mods ) { }
static void grapik::Input::ScrollWell ( GLFWwindow* window, double xoffset, double yoffset ) { }
static void grapik::Input::FreamBufferResize ( GLFWwindow* window, int width, int height ) { }
static void grapik::Input::Caracters ( GLFWwindow* window, unsigned int codepoint ) { }