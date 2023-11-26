#ifndef GRAPIK
#define GRAPIK

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

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
// error codes
enum Status {
    SUCCESS,
        // window
    FAILED_LOAD_GLAD,
    FAILED_CREATING_WINDOW,
    ALDREADY_CLOSED,
        // manager 
    ALREADY_DEFINED,
    FAILED_LOADING_RESOURCE,
        // shader
    FAILED_LOADING_SHADER,
    FAILED_COMPILING_SHADER,
    FAILED_COMPILING_PROGRAM,
    FAILED_LINKING_SHADER,
        // texture
    FAILED_LOAD_IMAGE,
        // model
        // text
    FAILED_INIT_FREETYPE,
    FAILED_LOAD_FONT,
    FAILED_LOAD_GLYPH
};

// Internal variables
namespace Internal {
    static GLFWwindow* window;
    static unsigned int SCR_WIDTH;
    static unsigned int SCR_HEIGTH;    
} /*Internal*/

// this namespace is ment to be used for defining Input function external to the main namespace
namespace Input {
    static void Keyboard ( GLFWwindow* window, int key, int scancode, int action, int mode );
    static void Mouse ( GLFWwindow* window, double xpos, double ypos );
    static void ScrollWell ( GLFWwindow* window, double xoffset, double yoffset );
    static void FreamBufferResize ( GLFWwindow* window, int width, int height );
    static void Caracters ( GLFWwindow* window, unsigned int codepoint );
} /*Input*/


// this namespace collects evey object 
namespace Objects {
    
} // namespace Objects

// resource Manager
namespace Resource_Manager {
    namespace Resource {
        class Shader { public:
            int ID;
            Shader ( ) { };
            Shader ( const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr, const char* tessControlPath = nullptr, const char* tessEvalPath = nullptr ) 
            { Make ( vertexPath, fragmentPath, geometryPath, tessControlPath, tessEvalPath ); }
    
            int Make (  const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr, const char* tessControlPath = nullptr, const char* tessEvalPath = nullptr );

            void use() { glUseProgram(ID); }
            void setInt   ( const std::string &name, int value )                    const { glUniform1i  ( glGetUniformLocation ( ID, name.c_str() ), value ); }
            void setBool  ( const std::string &name, bool value )                   const { glUniform1i  ( glGetUniformLocation ( ID, name.c_str() ), (int)value ); }
            void setFloat ( const std::string &name, float value )                  const { glUniform1f  ( glGetUniformLocation ( ID, name.c_str() ), value ); }
            void setVec2  ( const std::string &name, float x, float y )             const { glUniform2f  ( glGetUniformLocation ( ID, name.c_str() ), x, y ); }
            void setVec3  ( const std::string &name, float x, float y, float z )    const { glUniform3f  ( glGetUniformLocation ( ID, name.c_str() ), x, y, z ); }
            void setVec4  ( const std::string &name, float x, float y, float z, float w ) { glUniform4f  ( glGetUniformLocation ( ID, name.c_str() ), x, y, z, w ); }
            void setVec2  ( const std::string &name, const glm::vec2 &value )       const { glUniform2fv ( glGetUniformLocation ( ID, name.c_str() ), 1, &value[0] ); }
            void setVec3  ( const std::string &name, const glm::vec3 &value )       const { glUniform3fv ( glGetUniformLocation ( ID, name.c_str() ), 1, &value[0] ); }
            void setVec4  ( const std::string &name, const glm::vec4 &value )       const { glUniform4fv ( glGetUniformLocation ( ID, name.c_str() ), 1, &value[0] ); }
            void setMat2  ( const std::string &name, const glm::mat2 &mat )         const { glUniformMatrix2fv ( glGetUniformLocation ( ID, name.c_str() ), 1, GL_FALSE, &mat[0][0] ); }
            void setMat3  ( const std::string &name, const glm::mat3 &mat )         const { glUniformMatrix3fv ( glGetUniformLocation ( ID, name.c_str() ), 1, GL_FALSE, &mat[0][0] ); }
            void setMat4  ( const std::string &name, const glm::mat4 &mat )         const { glUniformMatrix4fv ( glGetUniformLocation ( ID, name.c_str() ), 1, GL_FALSE, &mat[0][0] ); }
        private:
            int checkCompileErrors(GLuint shader, std::string type);
        };
        class Text { public:
            struct Character {
                unsigned int TextureID; // ID handle of the glyph texture
                glm::ivec2   Size;      // Size of glyph
                glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
                unsigned int Advance;   // Horizontal offset to advance to next glyph
            };

            FT_Library ft;
            std::map<GLchar, Character> Characters;
            unsigned int VAO, VBO;

            Text ( ) { }
            Text ( std::string font ) { Make ( font ); }

            int Make ( std::string font );
            int RenderText ( Shader &shader, std::string text, float init_x, float init_y, float scale, glm::vec3 color, float to_wrap, float wrap_h, int Max_Rows, int Start_Row );
        };
    } /*Resources*/
    template <typename T>
    static bool in ( std::unordered_map < std::string, T > map, std::string value );

    // std::unordered_map < std::string, Resource::Texture > Textures;
    std::unordered_map < std::string, Resource::Shader  > Shaders;
    // std::unordered_map < std::string, Resource::Model   > Models;
    std::unordered_map < std::string, Resource::Text    > Texts;

    // static int Load_Texture ( std::string name, const char *file, bool alpha );
    static int Load_Shader ( std::string name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr, const char* tessControlPath = nullptr, const char* tessEvalPath = nullptr );
    // static int Load_Model ( std::string name, const char *path, bool gamma = false );
    static int Load_Text ( std::string name, const char *font );

    // static Resource::Texture Get_Texture ( std::string name ) { return Textures[name]; };
    static Resource::Shader Get_Shader ( std::string name ) { return Shaders[name]; };
    // static Resource::Model Get_Model ( std::string name ) { return Models[name]; };
    static Resource::Text Get_Text ( std::string name ) { return Texts[name]; };

    static void Clear ( );    
} /*Resource_Manager*/

// this namespace collects every Gui object
namespace Gui {
    class Button { public:
        Button ( ) { }
        Button ( std::string text, int x, int y, int width, int heigth, void(*callback)( ) );
        ~Button() { }

        void Draw ( ReKat::grapik::Resource_Manager::Resource::Text &text, ReKat::grapik::Resource_Manager::Resource::Shader &shader ) {
            text.RenderText ( shader, name, X, Y, 1, glm::vec3{0,0,0}, w, h, 1, 0 );
            // sprite.Draw ( texture,{X,Y},{w,h},0,{1,1,1} );
        }
        void Update_mause ( double x, double y ) {
            std::cout << "uptated: " << x << " " << y << '\n'; 
            x -= X;
            y -= Y;
            if ( ( x > 0 && x < w ) && ( y > 0 && y < h ) ) 
            { _call(); }
        }
    private:
        std::string name;
        int X, Y;
        int w, h;
        void (* _call ) ( );
    };
} // namespace Gui

    // Basic Grapik functions
    static int Start ( std::string name, unsigned int SCR_WIDTH, unsigned int SCR_HEIGTH,  bool transparent = false, bool fullscreen = false, bool resizable = false );
    static int End ( ); 
    static int IsEnd ( );
    static void Terminate ( );
    static int SetIcon ( std::string path );
    static void Pool ( );
	
} /* Grapik */ } // ReKat

// Basic Grapik function Implementaion
namespace ReKat::grapik {
    static int Start 
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
        glfwSetCharCallback( Internal::window, Input::Caracters );

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if ( !gladLoadGLLoader ( (GLADloadproc)glfwGetProcAddress ) ) 
        { return FAILED_LOAD_GLAD; }

        glViewport ( 0, 0, Internal::SCR_WIDTH, Internal::SCR_HEIGTH );
        glEnable ( GL_CULL_FACE ); glEnable ( GL_BLEND ); 
        glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        return SUCCESS;
    }

    static int End ( ) { 
        if ( IsEnd() ) 
        { glfwSetWindowShouldClose( Internal::window, true); return SUCCESS; }
        else 
        { return ALDREADY_CLOSED; }
    }

    static void Terminate ( ) 
    { End(); glfwTerminate(); }

    static int IsEnd ( ) 
    { return !glfwWindowShouldClose(Internal::window); }

    static int SetIcon ( std::string path ) {
        GLFWimage images[1]; 
        images[0].pixels = stbi_load ( path.c_str () , &images[0].width, &images[0].height, 0, 4 ); //rgba channels 
        glfwSetWindowIcon ( Internal::window, 1, images ); 
        stbi_image_free ( images[0].pixels );

        return SUCCESS;
    }

    static void Pool ( ) 
    { glfwSwapBuffers ( Internal::window ); glfwPollEvents ( ); }
}

namespace ReKat::grapik::Resource_Manager::Resource {
    int Shader::Make
    ( const char* vertexPath, const char* fragmentPath, const char* geometryPath, const char* tessControlPath, const char* tessEvalPath ) {
        std::string vertexCode, fragmentCode, geometryCode, tessControlCode, tessEvalCode;
        std::ifstream vShaderFile, fShaderFile, gShaderFile, tcShaderFile, teShaderFile;

        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        tcShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        teShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
            // if geometry shader path is present, also load a geometry shader
            if ( geometryPath != nullptr) {
                gShaderFile.open(geometryPath);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
            if ( tessControlPath != nullptr ) {
                tcShaderFile.open(tessControlPath);
                std::stringstream tcShaderStream;
                tcShaderStream << tcShaderFile.rdbuf();
                tcShaderFile.close();
                tessControlCode = tcShaderStream.str();
            }
            if ( tessEvalPath != nullptr ) {
                teShaderFile.open(tessEvalPath);
                std::stringstream teShaderStream;
                teShaderStream << teShaderFile.rdbuf();
                teShaderFile.close();
                tessEvalCode = teShaderStream.str();
            }
        } catch (std::ifstream::failure& e) { return FAILED_LOADING_SHADER; }
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        if ( checkCompileErrors(vertex, "VERTEX") != SUCCESS ) 
        { return FAILED_COMPILING_SHADER; }
        
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        if ( checkCompileErrors ( fragment, "FRAGMENT" ) != SUCCESS ) 
        { return FAILED_COMPILING_SHADER; }

        // if geometry shader is given, compile geometry shader
        unsigned int geometry;
        if ( geometryPath != nullptr ) {
            const char * gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            if ( checkCompileErrors ( geometry, "GEOMETRY" ) != SUCCESS ) 
            { return FAILED_COMPILING_SHADER; }
        }
        // if tessellation control shader is given, compile tessellation shader
        unsigned int tessControl;
        if ( tessControlPath != nullptr ) {
            const char * tcShaderCode = tessControlCode.c_str();
            tessControl = glCreateShader(GL_TESS_CONTROL_SHADER);
            glShaderSource(tessControl, 1, &tcShaderCode, NULL);
            glCompileShader(tessControl);
            if ( checkCompileErrors(tessControl, "TESS_CONTROL") != SUCCESS ) 
            { return FAILED_COMPILING_SHADER; }

        }
        // if tessellation evaluation shader is given, compile tessellation shader
        unsigned int tessEval;
        if ( tessEvalPath != nullptr ) {
            const char * teShaderCode = tessEvalCode.c_str();
            tessEval = glCreateShader(GL_TESS_EVALUATION_SHADER);
            glShaderSource(tessEval, 1, &teShaderCode, NULL);
            glCompileShader(tessEval);
            if ( checkCompileErrors(tessEval, "TESS_EVALUATION") != SUCCESS ) 
            { return FAILED_COMPILING_SHADER; }
        }

        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if ( geometryPath != nullptr ) { glAttachShader(ID, geometry); }
        if ( tessControlPath != nullptr ) { glAttachShader ( ID, tessControl ); }
        if ( tessEvalPath != nullptr ) { glAttachShader ( ID, tessEval ); }

        glLinkProgram(ID);
        if ( checkCompileErrors(ID, "PROGRAM") != SUCCESS ) { return FAILED_LINKING_SHADER; }
        
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if ( geometryPath != nullptr ) { glDeleteShader ( geometry ); }
        if ( geometryPath != nullptr ) { glDeleteShader ( tessControl ); }
        if ( geometryPath != nullptr ) { glDeleteShader ( tessEval ); }

        return SUCCESS;
    }

    int Shader::checkCompileErrors 
    ( GLuint shader, std::string type ) {
        GLint success;
        GLchar infoLog[1024];
        if(type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success) { ReKat::grapik::FAILED_COMPILING_PROGRAM; }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) { ReKat::grapik::FAILED_COMPILING_SHADER; }
        }
        return ReKat::grapik::SUCCESS;
    }

    int Text::Make
    ( std::string font ) {
        if ( FT_Init_FreeType ( &ft ) ) 
        { return FAILED_INIT_FREETYPE; }

        // find path to font
        if ( font.empty ( ) ) { return FAILED_LOAD_FONT; }
        
        // load font as face
        FT_Face face;
        if ( FT_New_Face ( ft, font.c_str(), 0, &face ) ) { return FAILED_LOAD_FONT; }
        else {
            // set size to load glyphs as
            FT_Set_Pixel_Sizes(face, 0, 48);

            // disable byte-alignment restriction
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            // load first 128 characters of ASCII set
            for (unsigned char c = 0; c < 128; c++)
            {
                // Load character glyph 
                if (FT_Load_Char(face, c, FT_LOAD_RENDER)) { continue; }
                // generate texture
                unsigned int texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D( GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer );

                // set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                // now store character for later use
                Character character = { texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
                };
                Characters.insert( {c, character} );
            }
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        // destroy FreeType once we're finished
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        
        // configure VAO/VBO for texture quads
        // -----------------------------------
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return SUCCESS;
    }

    int Text::RenderText 
    ( Shader &shader, std::string text, float init_x, float init_y, float scale, glm::vec3 color, float to_wrap, float wrap_h, int Max_Rows, int Start_Row ) {
        // activate corresponding render state	
        shader.use();
        glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        // iterate through all characters
        std::string::const_iterator c;
        int x = init_x, y = init_y;

        y -= (scale * wrap_h ) * Start_Row;
        int last_y = init_y - (scale * wrap_h ) * Max_Rows;
        int Rows = 0;
    
        for (c = text.begin(); c != text.end(); c++) {
            // new line check
            if ( *c == '\n' ) { y -= (scale * wrap_h ); Rows++; x = init_x; continue; }
            // last line chiek
            Character ch = Characters[*c];
            // text wrapping
            if ( x + ch.Size.x >= ( to_wrap + init_x ) ) { y -= (scale * wrap_h ); Rows++; x = init_x; }
            if ( ! ( y <= last_y ) ) { 

                float xpos = x + ch.Bearing.x * scale;
                float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

                float w = ch.Size.x * scale;
                float h = ch.Size.y * scale;
                // update VBO for each character
                float vertices[6][4] = {
                    { xpos,     ypos + h,   0.0f, 0.0f },            
                    { xpos,     ypos,       0.0f, 1.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },

                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },
                    { xpos + w, ypos + h,   1.0f, 0.0f }           
                };
                // render glyph texture over quad
                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                // update content of VBO memory
                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                // render quad
                glDrawArrays(GL_TRIANGLES, 0, 6);
                // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
                x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
            }

        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        return Rows;
    }   
}

namespace ReKat::grapik::Gui {
    Button::Button ( std::string text, int x, int y, int width, int heigth, void(*callback)( ) ) 
    : name(text), X(x), Y(y), w(width), h(heigth), _call(callback) { }
}

// Resources Manager Implementation
namespace ReKat::grapik::Resource_Manager {
    template <typename T>
    static bool in ( std::unordered_map < std::string, T > map, std::string value ) {
        for ( auto p : map ) 
        { if ( p.first == value ) { return true;} }
        return false;
    }

    static int Load_Shader 
    ( std::string name, const char* vertexPath, const char* fragmentPath, const char* geometryPath, const char* tessControlPath, const char* tessEvalPath ) {
        if ( in <Resource::Shader> ( Shaders, name ) ) { return ALREADY_DEFINED; }

        Resource::Shader T;
        if ( T.Make ( vertexPath, fragmentPath, geometryPath, tessControlPath, tessEvalPath ) != SUCCESS ) { return FAILED_LOADING_RESOURCE; }

        Shaders.insert({name,T});
        return SUCCESS;
    }

    static int Load_Text 
    ( std::string name, const char *font ) {
        if ( in <Resource::Text> ( Texts, name ) ) { return ALREADY_DEFINED; }

        Resource::Text T;
        int p;
        if ( p = T.Make ( font ) != SUCCESS ) { std::cout << "error: "<< p << '\n'; return FAILED_LOADING_RESOURCE; }

        Texts.insert({name,T});
        return SUCCESS;
    }
}

#endif