#include "api.hpp"

// imamge
#include <kat_grapik/stb_image.hpp>

kat::grapik::Renderer::Renderer ( std::string name, bool transparent, bool fullscreen )
	: _name(name),
	_fullScreen(fullscreen)
{
	std::cout << "init\n";
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, 1);

	if ( transparent ) {
		std::cout << "starting in transparent\n";
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
		glfwWindowHint(GLFW_DECORATED, 0);
	}

	if ( fullscreen ) {
		glfwWindowHint(GLFW_DECORATED, 0);
	}

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	
	if ( fullscreen ) {
		GLFWmonitor* _monitor =  glfwGetPrimaryMonitor ( );
    	_window = glfwCreateWindow(16, 9, name.c_str() , _monitor, NULL );
    	
		// const GLFWvidmode* _mode = glfwGetVideoMode ( _monitor );
		//glfwSetWindowSize(_window, _mode->width, _mode->height );

		std::cout << "start in fullscreen\n";
	} else 
	{ _window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name.c_str(), NULL, NULL); }

    if ( _window == NULL ) {
        glfwTerminate();
        std::cout << ("Failed to create GLFW window\n");
        throw ("Failed to create GLFW window");
    }
    
    glfwMakeContextCurrent( _window );
    glfwSetKeyCallback( _window, keyboard );					// key controll
    glfwSetFramebufferSizeCallback(_window, window_resize );	// canvas resize
    glfwSetCursorPosCallback(_window, mouse);					// mouse movement
    glfwSetScrollCallback(_window, scroll);						// scroll movement

    glfwSetWindowOpacity( _window, 1.0f);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if ( !gladLoadGLLoader ( (GLADloadproc) glfwGetProcAddress ) ) 
	{ throw ("Failed to initialize GLAD"); }

	// OpenGL state
    // ------------
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void kat::grapik::Renderer::End ( ) {
	if (_window != NULL ) 
		glfwSetWindowShouldClose(_window, true);
}

kat::grapik::Renderer::~Renderer ( ) {
	glfwTerminate();
}

bool kat::grapik::Renderer::IsEnd ( ) {
	return !glfwWindowShouldClose(_window); 
}

void kat::grapik::Renderer::Pool ( ) {
	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

void kat::grapik::Renderer::SetIcon ( std::string path ) {
    GLFWimage images[1]; 
    images[0].pixels = stbi_load ( path.c_str () , &images[0].width, &images[0].height, 0, 4 ); //rgba channels 
    glfwSetWindowIcon(_window, 1, images); 
    stbi_image_free(images[0].pixels);
}

void kat::grapik::Renderer::Borderless ( ) {
	std::cout << "b\n";	
	glfwWindowHint(GLFW_DECORATED, 0);
}