#ifndef Kat_Grapik
#define Kat_Grapik

#pragma once

// window
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

// calculations
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// model loading
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// utility
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <kat_grapik/shader.hpp>
#include <kat_grapik/ResourceManager.hpp>
#include <kat_grapik/text.hpp>

namespace kat {
namespace grapik {
	#define window GLFWwindow*

	class Renderer {
	private:
		std::string _name;
		window _window;
		unsigned int SCR_WIDTH = 800;
		unsigned int SCR_HEIGHT = 600;
		bool _fullScreen;
	
		static void keyboard		( window _window, int _key, int _scancode, int _action, int _mode );
		static void mouse			( window _window, double _xposIn, double _yposIn );
		static void window_resize	( window _window, int _width, int _height );
		static void scroll			( window _window, double _xoffset, double _yoffset );
		
		/*
		static Renderer& getInstance ( ) 
		{ static Renderer instance; return instance; }

		static void _keyboard( window _window, int _key, int _scancode, int _action, int _mode )
		{ getInstance().keyboard( _window, _key, _scancode, _action, _mode ); }
		static void _mouse( window _window, double _xposIn, double _yposIn )
		{ getInstance().mouse( _window, _xposIn, _yposIn ); }
		static void _window_resize( window _window, int _width, int _height )
		{ getInstance().window_resize( _window, _width, _height  ); }
		static void _scroll( window _window, double _xoffset, double _yoffset )
		{ getInstance().scroll( _window, _xoffset, _yoffset ); }*/
	public:
		TextRenderer *Text;
		 

		 Renderer ( std::string name, bool transparent = false, bool fullscreen = false );
		 Renderer ( ) { std::cout << "instance\n"; }
		~Renderer ( );

		bool RenderLoop ( );

		void SetIcon ( std::string path );
		void Pool ( );

		bool IsEnd ( );
		void End ( );

		void Borderless ( );

	};
} // namespace grapik
} // namespace kat


#endif