#ifndef MANAGER
#define MANAGER
#include "text.h"
#include "sprite.h"
#include "shader.h"
#include "texture.h"
#include "tilemap.h"

#include <map>

namespace Manager {
    static std::map < std::string, Text* >    Texts;
    static std::map < std::string, Shader* >  Shaders;
    static std::map < std::string, Sprite* >  Sprites;
    static std::map < std::string, Texture* > Textures;
    static std::map < std::string, Tilemap* > Tilemaps;

// Shader logic
    static Shader* Shader_Get  ( std::string name ) 
    { return Shaders [name]; }
    static int Shader_Load ( std::string name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr, const char* tessControlPath = nullptr, const char* tessEvalPath = nullptr ) {
        Shader *s = new Shader ( );
        Shaders.insert( { name, s } );
        return (*s).Make( vertexPath, fragmentPath, geometryPath, tessControlPath, tessEvalPath );
    }
// Texture logic
    static Texture* Texture_Get  ( std::string name ) 
    { return Textures [name]; }
    static int Texture_Load ( std::string name, const char* path ) {
        Texture *t = new Texture ( );
        Textures.insert( { name, t} );
        return (*t).Make(path);
    }
// Text logic
    static Text* Text_Get  ( std::string name ) 
    { return Texts [name]; }
    static int Text_Load ( std::string name, const char* path, std::string shader ) {
        Text *t = new Text ( );
        Texts.insert( { name, t } );
        return (*t).Make(path, Shaders[shader]);
    }
// Sprite login 
    static Sprite* Sprite_Get  ( std::string name ) 
    { return Sprites [name]; }
    static int Sprite_Load ( std::string name, std::string shader, std::string texture, glm::vec2 set = {1,1} ) {
        Sprite *s = new Sprite ( Shaders[shader], Textures[texture], set );
        Sprites.insert( { name, s } );
        return 0;
    }
// Tilemap login 
    static Tilemap* Tilemap_Get  ( std::string name ) 
    { return Tilemaps [name]; }
    static int Tilemap_Load ( std::string name, std::string sprite, std::string path ) {
        Tilemap *t = new Tilemap ( Sprites[sprite] );
        Tilemaps.insert( { name, t } );
        return (*t).Make ( path );
    }

}; // namespace Manager


#endif