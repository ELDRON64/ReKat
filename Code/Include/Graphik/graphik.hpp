#ifdef GRAPIK
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
namespace Internal {
    
}

namespace Input {
    static void Keyboard ( );
    static void Mouse ( );
    static void ScrollWell ( );
    static void FreamBufferResize ( );
}

    static void Start ( );
} }

#endif