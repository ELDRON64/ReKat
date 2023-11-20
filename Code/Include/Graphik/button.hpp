#ifndef BUTTON
#define BUTTON
#include "text.hpp"

class button {
private:
    std::string name;
    int X, Y;
    int w, h;
    void (* _call ) ();
public:
    button( std::string text, int x, int y, int width, int heigth, void(*callback)( ) );
    ~button() { }

    void Draw ( Text &text, Shader &shader );
    void Update_mause ( double x, double y );
};

button::button( std::string text, int x, int y, int width, int heigth, void(*callback)( ) ) 
: name(text), X(x), Y(y), w(width), h(heigth), _call(callback) { }

void button::Draw ( Text &text, Shader &shader ) {
    text.RenderText ( shader, name, X, Y, 1, glm::vec3{0,0,0}, w, h, 1, 0 );
}

void button::Update_mause ( double x, double y ) {
    std::cout << "uptated: " << x << " " << y << '\n'; 
    x -= X;
    y -= Y;
    if ( ( x > 0 && x < w ) && ( y > 0 && y < h ) ) 
    { _call(); }
}

#endif