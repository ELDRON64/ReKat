#pragma once

#define OPENGL
#include "command.hpp"

static void grapik::Input::Keyboard ( GLFWwindow* window, int key, int scancode, int action, int mode ) {
    if ( key == GLFW_KEY_ESCAPE ) { grapik::End(); }

    // shift
    if ( key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT ) {
        if ( action == GLFW_PRESS ) { shift = true; } 
        else { shift = false; }
    }
    // ctrl
    if ( key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL ) {
        if ( action == GLFW_PRESS ) { ctrl = true; } 
        else { ctrl = false; }
    }

    if ( ( action == GLFW_PRESS || action == GLFW_REPEAT ) ) {
        if ( key == GLFW_KEY_ESCAPE ) { grapik::End(); }
        if ( key == GLFW_KEY_ENTER ) { execute_command ();  return; }
        if ( key == GLFW_KEY_DELETE || key == GLFW_KEY_BACKSPACE ) 
        { if ( history[current_command].size() > 0 ) { history[current_command].pop_back (); } return; }
        if ( key == GLFW_KEY_DOWN ) 
        { if ( current_command < history.size( ) - 1 ) { current_command ++; } return; }
        if ( key == GLFW_KEY_UP ) 
        { if ( current_command > 0) { current_command --; }  return; }
    }
}
static void grapik::Input::Mouse ( GLFWwindow* window, double xposIn, double yposIn ) { }
static void grapik::Input::ScrollWell ( GLFWwindow* window, double xoffset, double yoffset ) {
    if ( yoffset >= 0 ) { start_line ++; }
    if ( yoffset <= 0 ) { start_line --; }
}
static void grapik::Input::FreamBufferResize ( GLFWwindow* window, int width, int height ) {
    glViewport ( 0, 0, SCR_WIDTH = width, SCR_HEIGHT = height );
}
static void grapik::Input::Caracters ( GLFWwindow* window, unsigned int codepoint ) {
    history[current_command] += (char)(codepoint);
}