#ifndef BUTTON
#define BUTTON
#include "text.h"
#include "sprite.h"

class Button {
private:
    bool hower = false;
    void (* _call ) ();
public:
    std::string name;
    double last_x, last_y;
    int X, Y;
    int w, h;
    Button( std::string text, int x, int y, int width, int heigth, void(*callback)( ) );
    ~Button() { }

    void Draw ( Text &text, Shader &shader, Sprite &sprite, Texture &texture, int SCR_H );
    void Update_mause ( double x, double y );
    void Pressed ( );
};

Button::Button( std::string text, int x, int y, int width, int heigth, void(*callback)( ) ) 
: name(text), X(x), Y(y), w(width), h(heigth), _call(callback) { }

void Button::Draw ( Text &text, Shader &shader, Sprite &sprite, Texture &texture, int SCR_H ) {
    sprite.Draw ( &texture,{X,Y},{w,h},0,{1,1,1} );
    text.RenderText ( shader, name, X, Y+h/2, 1, glm::vec3{0,0,0}, w, h, 1, 0 );
}

void Button::Update_mause ( double _x, double _y ) {
    last_x = _x - X;
    last_y = _y - Y;
    if ( ( last_x > 0 && last_x < w ) && ( last_y > 0 && last_y < h ) ) 
    { hower = true; } else { hower = false; }
    last_x = _x; last_y = _y;
}

void Button::Pressed ( ) { 
    if ( hower ) { _call(); } 
    Update_mause ( last_x, last_y );
    std::cout << "x: " << last_x << " y: " << last_y;
}

#endif