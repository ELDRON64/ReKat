#include "render.hpp"

int main(int argc, char const *argv[]) {
    Init();

    while (grapik::IsEnd()) {
        Render();
    }
    grapik::Terminate ( );
    
    return 0;
}
