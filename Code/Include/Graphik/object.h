#ifndef OBJECT_H
#define OBJECT_H

#include "sprite.h"

class Object {
private:
    // transform
    glm::vec2 position;
    glm::vec2 size;
    Sprite* sprite;
    int frame;
public:
    Object ( ) { }
    Object ( Sprite *sprite, glm::vec2 pos, glm::vec2 size ) : sprite(sprite), position(pos), size(size) { }

    void DMove ( glm::vec2 move ) { position += move; }
    void Move  ( glm::vec2 new_pos ) { position = new_pos; }
    char* packpos ( ) 
    { return (char*) & position; }
    
    void Change_frame ( int _frame ) { frame = _frame; }
    void Draw  ( ) 
    { sprite->Draw_frame ( frame, position, size, 0 ); }
};



#endif