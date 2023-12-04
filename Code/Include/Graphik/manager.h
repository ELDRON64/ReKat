#ifndef MANAGER
#define MANAGER
#include "text.h"
#include "sprite.h"
#include "shader.h"
#include "texture.h"

#include <map>

class Manager {
private:
    Manager ( ) {}

public:
    static std::map < std::string, Text >    Texts;
    static std::map < std::string, Shader >  Shaders;
    static std::map < std::string, Sprite >  Sprites;
    static std::map < std::string, Texture > Textures;

// Shader logic
    static inline Shader Shader_Get  ( std::string name ) 
    { return Shaders [name]; }
    static int Shader_Load ( std::string name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr, const char* tessControlPath = nullptr, const char* tessEvalPath = nullptr ) {
        Shaders.insert( { name, Shader ( ) } );
        return Shader_Get(name).Make( vertexPath, fragmentPath, geometryPath, tessControlPath, tessEvalPath );
    }
// Texture logic
    static inline Texture Texture_Get  ( std::string name ) 
    { return Textures [name]; }
    static int Texture_Load ( std::string name, const char* path ) {
        Textures.insert( { name, Texture ( ) } );
        return Texture_Get(name).Make(path);
    }
// Text logic
    static inline Text Text_Get  ( std::string name ) 
    { return Texts [name]; }
    static int Text_Load ( std::string name, const char* path, std::string shader ) {
        Texts.insert( { name, Text ( ) } );
        return Text_Get(name).Make(path, &Shaders[shader]);
    }
// Sprite login 
    static inline Sprite Sprite_Get  ( std::string name ) 
    { return Sprites [name]; }
    static int Sprite_Load ( std::string name, std::string shader, std::string texture, glm::vec2 set = {1,1} ) {
        Sprites.insert( { name, Sprite ( Shaders[shader], Textures[texture], set) } );
        return 0;
    }

}; // namespace Manager


#endif