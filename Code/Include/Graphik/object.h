#ifndef OBJECT_H
#define OBJECT_H

#include "sprite.h"

class Object {
protected:
    // transform
    glm::vec2 pos;
    glm::vec2 size;
    Sprite* sprite;
    int frame;
public:
    Object ( ) { }
    Object ( Sprite *sprite, glm::vec2 _pos, glm::vec2 _size ) : sprite(sprite), pos(_pos), size(_size) { }

    void DMove ( glm::vec2 move ) { pos += move; }
    void Move  ( glm::vec2 new_pos ) { pos = new_pos; }
    char* packpos ( ) 
    { return (char*) & pos; }

    glm::vec2 Get_pos ( ) { return pos; }
    glm::vec2 Get_size ( ) { return size; }
    
    void Change_frame ( int _frame ) { frame = _frame; }
    void Draw  ( ) 
    { sprite->Draw_frame ( frame, pos, size, 0 ); }
};



#endif