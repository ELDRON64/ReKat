#ifndef GRAPIK
#define GRAPIK

#include <iostream>
#include <map>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace ReKat {
namespace grapik {
    enum Status {
        SUCCESS,
        FAILED_LOAD_GLAD,
        FAILED_CREATING_WINDOW,
        ALDREADY_CLOSED
    };

namespace Internal {
    static GLFWwindow* window;
    static unsigned int SCR_WIDTH;
    static unsigned int SCR_HEIGTH;    
} /*Internal*/

namespace Input {
    static void Keyboard ( GLFWwindow* window, int key, int scancode, int action, int mode );
    static void Mouse ( GLFWwindow* window, double xpos, double ypos );
    static void ScrollWell ( GLFWwindow* window, double xoffset, double yoffset );
    static void FreamBufferResize ( GLFWwindow* window, int width, int height );
} /*Input*/

    static int Start ( std::string name, unsigned int SCR_WIDTH, unsigned int SCR_HEIGTH,  bool transparent = false, bool fullscreen = false, bool resizable = false );
    static int End ( ); 
    static int IsEnd ( );
    static int SetIcon ( std::string path );
    static void Pool ( );
	
} /* Grapik */ } // ReKat

static int ReKat::grapik::Start 
( std::string name, unsigned int SCR_WIDTH, unsigned int SCR_HEIGTH,  bool transparent, bool fullscreen, bool resizable ) {
    Internal::SCR_HEIGTH = SCR_HEIGTH; Internal::SCR_WIDTH = SCR_WIDTH;

    glfwInit ( );
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
#ifdef __APPLE__
    glfwWindowHint ( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
#endif
    if ( transparent ) {
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
		glfwWindowHint(GLFW_DECORATED, 0);
	}

	if ( fullscreen ) { glfwWindowHint(GLFW_DECORATED, 0); }

    glfwWindowHint ( GLFW_RESIZABLE, resizable );

    if ( fullscreen ) {
		GLFWmonitor* _monitor =  glfwGetPrimaryMonitor ( );
    	Internal::window = glfwCreateWindow(16, 9, name.c_str() , _monitor, NULL );
		// const GLFWvidmode* _mode = glfwGetVideoMode ( _monitor );
		//glfwSetWindowSize(Internal::window, _mode->width, _mode->height );
	} else 
	{ Internal::window = glfwCreateWindow ( Internal::SCR_WIDTH, Internal::SCR_HEIGTH, name.c_str(), nullptr, nullptr ); }

    if ( Internal::window == NULL ) 
    { glfwTerminate(); return FAILED_CREATING_WINDOW; }

    glfwMakeContextCurrent ( Internal::window );
    glfwSetKeyCallback ( Internal::window, Input::Keyboard );
    glfwSetCursorPosCallback ( Internal::window, Input::Mouse );
    glfwSetScrollCallback ( Internal::window, Input::ScrollWell );
    glfwSetFramebufferSizeCallback ( Internal::window, Input::FreamBufferResize );

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if ( !gladLoadGLLoader ( (GLADloadproc)glfwGetProcAddress ) ) 
    { return FAILED_LOAD_GLAD; }

    glViewport ( 0, 0, Internal::SCR_WIDTH, Internal::SCR_HEIGTH );
    glEnable ( GL_BLEND ); glEnable ( GL_CULL_FACE );
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    return SUCCESS;
}

static int ReKat::grapik::End ( ) { 
    if ( Internal::window != NULL ) 
    { glfwSetWindowShouldClose( Internal::window, true); glfwTerminate(); return SUCCESS; }
    else 
    { return ALDREADY_CLOSED; }
       
}

static int ReKat::grapik::IsEnd ( ) 
{ return !glfwWindowShouldClose(Internal::window); }

static int ReKat::grapik::SetIcon ( std::string path ) {
    GLFWimage images[1]; 
    images[0].pixels = stbi_load ( path.c_str () , &images[0].width, &images[0].height, 0, 4 ); //rgba channels 
    glfwSetWindowIcon ( Internal::window, 1, images ); 
    stbi_image_free ( images[0].pixels );

    return SUCCESS;
}

static void ReKat::grapik::Pool ( ) {
	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers ( Internal::window );
    glfwPollEvents ( );
}

#endif