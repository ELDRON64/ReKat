#ifndef GRAPIK
#define GRAPIK

#include <iostream>
#include <map>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace ReKat {
namespace grapik {
    enum Status {
        SUCCESS,
        FAILDE_LOAD_GLAD 
    }

namespace Internal {
    static GLFWwindow* window;
    
} /*Internal*/

namespace Input {
    static void Keyboard ( GLFWwindow* window, int key, int scancode, int action, int mode );
    static void Mouse ( GLFWwindow* window, double xpos, double ypos );
    static void ScrollWell ( GLFWwindow* window, double xoffset, double yoffset );
    static void FreamBufferResize ( GLFWwindow* window, int width, int height );
} /*Input*/

    static void Start ( );

    static void END ( ); 
} /* Grapik */ } // ReKat

static void ReKat::Grapik::Start ( ) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ) 
    { return FAILDE_LOAD_GLAD; }

    glfwSetKeyCallback(window, Keyboard);
    glfwSetCursorPosCallback(window, Mouse);
    glfwSetScrollCallback(window, ScrollWell);
    glfwSetFramebufferSizeCallback(window, FreamBufferResize);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return SUCCESS;
}

static void ReKat::grapik::END ( ) {
    glfwTerminate();

    return SUCCESS;
}


#endif