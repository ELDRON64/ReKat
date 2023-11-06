#include <iostream>
#include <ReKat.hpp>
using namespace ReKat::grapik;

static void ReKat::grapik::Input::Keyboard ( GLFWwindow* window, int key, int scancode, int action, int mode ) { 
    ReKat::grapik::End(); 
}
static void ReKat::grapik::Input::Mouse ( GLFWwindow* window, double xpos, double ypos ) { }
static void ReKat::grapik::Input::ScrollWell ( GLFWwindow* window, double xoffset, double yoffset ) { }
static void ReKat::grapik::Input::FreamBufferResize ( GLFWwindow* window, int width, int height ) { }

int main ( ) 
{ 
    Start ( "cok departement ", 800, 600 );
    //std::cout << "shader loaded: " << Resource_Manager::Load_Shader ( "text","Shaders/text.vs","Shaders/text.fs" );
    Resource_Manager::Load_Shader ( "basic","Shaders/basic.vs","Shaders/basic.fs" );
    Resource_Manager::Load_Shader ( "texture","Shaders/texture.vs","Shaders/texture.fs" );
    //std::cout << "\nFont loaded: " << Resource_Manager::Load_Text ( "antonio", "Antonio-Bold.ttf", 13, "text" );
    //Resource_Manager::Resource::text T = Resource_Manager::Get_Text ("text");
    SetIcon( "Eldron.png" );

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    std::cout << "texture load: " << Resource_Manager::Load_Texture ("Eldron","Eldron.png");

    while ( IsEnd( ) ) {
        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Resource_Manager::Get_Shader("texture").use();
        Resource_Manager::Get_Texture("Eldron").Bind();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //T.Render( "Il COK Departement", 0, 0, 1.0f, {0.4f,0.3f,0.1f});

        Pool( );
    }

    Terminate();
}
