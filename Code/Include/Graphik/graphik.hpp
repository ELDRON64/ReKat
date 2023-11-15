#ifndef GRAPIK
#define GRAPIK

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

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

// resource Manager
namespace Resource_Manager {
    namespace Resource {
        class texture {
        public:
            texture ( );
            int Make ( const char *file );
        public:
            // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
            unsigned int ID;
            // texture image dimensions
            unsigned int Width, Height; // width and height of loaded image in pixels
            // texture Format
            unsigned int Format; // format of texture object
            // texture configuration
            unsigned int Wrap_S; // wrapping mode on S axis
            unsigned int Wrap_T; // wrapping mode on T axis
            unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
            unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels
            // binds the texture as the current active GL_TEXTURE_2D texture object
            void Bind ( );
        };
        class shader {
        public:
            int ID;
            shader ( ) { };
            int Make (  const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr, const char* tessControlPath = nullptr, const char* tessEvalPath = nullptr );

            void use ( ) { glUseProgram(ID); }
            void setBool  ( const std::string &name, bool value )                   const { glUniform1i  ( glGetUniformLocation ( ID, name.c_str() ), (int)value ); }
            void setInt   ( const std::string &name, int value )                    const { glUniform1i  ( glGetUniformLocation ( ID, name.c_str() ), value ); }
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
        class model {
        public:
            model ( ) { }
            int Make ( const char *path, bool gamma = false );
        }; 
        class text {
            private:
                struct Character {
                    unsigned int TextureID;
                    glm::ivec2   Size;
                    glm::ivec2   Bearing;
                    unsigned int Advance;
                };
                unsigned int VAO, VBO;

                std::map<char, Character> Characters;
                std::string TextShader;
            public:
                text ( ) { };
                int Make ( const char *font, unsigned int font_size, std::string text_shader );
                void Render ( std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f) );
        };
    } /*Resources*/
    template <typename T>
    static bool in ( std::unordered_map < std::string, T > map, std::string value );

    std::unordered_map < std::string, Resource::texture > Textures;
    std::unordered_map < std::string, Resource::shader  > Shaders;
    std::unordered_map < std::string, Resource::model   > Models;
    std::unordered_map < std::string, Resource::text    > Texts;

    static int Load_Texture ( std::string name, const char *file );
    static int Load_Shader ( std::string name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr, const char* tessControlPath = nullptr, const char* tessEvalPath = nullptr );
    static int Load_Model ( std::string name, const char *path, bool gamma = false );
    static int Load_Text ( std::string name, const char *font, unsigned int fontSize, std::string shader );

    static Resource::texture Get_Texture ( std::string name ) { return Textures[name]; };
    static Resource::shader Get_Shader ( std::string name ) { std::cout << "geting shader::" << name << " " << Shaders[name].ID << '\t'; return Shaders[name]; };
    static Resource::model Get_Model ( std::string name ) { return Models[name]; };
    static Resource::text Get_Text ( std::string name ) { return Texts[name]; };

    static void Clear ( );    
} /*Resource_Manager*/

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
    { glfwTerminate(); }

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

// Resource Implementation
namespace ReKat::grapik::Resource_Manager::Resource {
    texture::texture ( ) : Width(0), Height(0), Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR) 
    { glGenTextures(1, &this->ID); }

    int texture::Make ( const char *file ) {
        // load image
        int width, height, nrChannels;
        unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

        if (data) {
            this->Width = width;
            this->Height = height;

            if (nrChannels == 1)
                Format = GL_RED;
            else if (nrChannels == 3)
                Format = GL_RGB;
            else if (nrChannels == 4)
                Format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, this->ID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
            
            glTexImage2D(GL_TEXTURE_2D, 0, Format, width, height, 0, Format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, 0);
        } else { stbi_image_free(data); return FAILED_LOAD_IMAGE; }

        stbi_image_free(data);
        return SUCCESS; 
    }

    void texture::Bind ( ) 
    { glBindTexture(GL_TEXTURE_2D, this->ID); }


    int shader::Make ( const char* vertexPath, const char* fragmentPath, const char* geometryPath, const char* tessControlPath, const char* tessEvalPath ) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
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
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return SUCCESS;
    }

    int shader::checkCompileErrors(GLuint shader, std::string type) {
        GLint success;
        GLchar infoLog[1024];
        if(type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                return FAILED_COMPILING_PROGRAM;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                return FAILED_LINKING_SHADER;
            }
        }
        return SUCCESS;
    }

    int model::Make ( const char *path, bool gamma ) { return SUCCESS; }

    int text::Make ( const char *font, unsigned int font_size, std::string text_shader ){
        TextShader = text_shader;
        // load and configure shader
        shader text_shader_s = ReKat::grapik::Resource_Manager::Get_Shader ( text_shader );
        text_shader_s.setMat4 ( "projection", glm::ortho(0.0f, static_cast<float>(Internal::SCR_WIDTH), static_cast<float>(Internal::SCR_HEIGTH), 0.0f) );
        text_shader_s.setInt ( "text", 0 );

        // configure VAO/VBO for texture quads
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // first clear the previously loaded Characters
        this->Characters.clear();
        // then initialize and load the FreeType library
        FT_Library ft;    
        if (FT_Init_FreeType(&ft)) { return FAILED_INIT_FREETYPE; }
        // load font as face
        FT_Face face;
        if (FT_New_Face(ft, font, 0, &face)) { return FAILED_LOAD_FONT; }
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, font_size);
        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
        // then for the first 128 ASCII characters, pre-load/compile their characters and store them
        for (GLubyte c = 0; c < 128; c++) // lol see what I did there 
        {
            // FAILED_LOAD_GLYPH
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) { continue; }

            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
                );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        // destroy FreeType once we're finished
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        return SUCCESS;
    };

    void text::Render ( std::string text, float x, float y, float scale, glm::vec3 color ) {
        shader text_shader_s = ReKat::grapik::Resource_Manager::Get_Shader ( TextShader );
        text_shader_s.use();
        text_shader_s.setVec3("textColor", color);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(this->VAO);

        // iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++) {
            Character ch = Characters[*c];

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 0.0f },
                { xpos,     ypos,       0.0f, 0.0f },

                { xpos,     ypos + h,   0.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 0.0f }
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph
            x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

// Resources Manager Implementation
namespace ReKat::grapik::Resource_Manager {
    template <typename T>
    static bool in ( std::unordered_map < std::string, T > map, std::string value ) {
        for ( auto p : map ) 
        { if ( p.first == value ) { return 1;} }
        return 0;
    }
    
    static int Load_Texture 
    ( std::string name, const char *file ) {
        if ( in <Resource::texture> ( Textures, name ) ) { return ALREADY_DEFINED; }

        Resource::texture T;
        if ( T.Make (file) != SUCCESS ) { return FAILED_LOADING_RESOURCE; }

        Textures.insert({name,T});
        return SUCCESS;
    }

    static int Load_Shader 
    ( std::string name, const char* vertexPath, const char* fragmentPath, const char* geometryPath, const char* tessControlPath, const char* tessEvalPath ) {
        if ( in <Resource::shader> ( Shaders, name ) ) { return ALREADY_DEFINED; }

        Resource::shader T;
        if ( T.Make ( vertexPath, fragmentPath, geometryPath, tessControlPath, tessEvalPath ) != SUCCESS ) { return FAILED_LOADING_RESOURCE; }
        std::cout << "created shader at: " << T.ID << '\n';

        Shaders.insert({name,T});
        return SUCCESS;
    }

    static int Load_Model 
    ( std::string name, const char *path, bool gamma ) {
        if ( in <Resource::model> ( Models, name ) ) { return ALREADY_DEFINED; }

        Resource::model T;
        if ( T.Make ( path, gamma ) != SUCCESS ) { return FAILED_LOADING_RESOURCE; }

        Models.insert({name,T});
        return SUCCESS;
    }

    static int Load_Text 
    ( std::string name, const char *font, unsigned int font_size, std::string shader ) {
        if ( in <Resource::text> ( Texts, name ) ) { return ALREADY_DEFINED; }

        Resource::text T;
        int p;
        if ( p = T.Make (font,font_size,shader) != SUCCESS ) { std::cout << "error: "<< p << '\n'; return FAILED_LOADING_RESOURCE; }

        Texts.insert({name,T});
        return SUCCESS;
    }

}

#endif