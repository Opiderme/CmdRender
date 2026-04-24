// hello world program in C++17
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "CmdRender/CmdRender.h"
#include "CmdRender/2dEntity/Shape2d.h"

int main() {
    CmdRender renderer("HelloWorld", 629, 320, {255, 0, 0}); // Create a CmdRender instance with a black background
    Shape2d square("square", 50, 40, 100, 100, {0, 255, 0}, {0, 255, 0}); // Create a square shape with red outline and green fill
    Shape2d triangle("triangle", 200, 40, 50, 50, {0, 0, 255}, {0, 0, 255});
    Shape2d cross("cross", 350, 40, 30, 30, {255, 255, 0}, {255, 255, 0});
    Shape2d diamond("diamond", 500, 40, 50, 50, {0, 255, 255}, {0, 255, 255});

    while (true){
        square.mouvX(4); // Move the square shape horizontally by 1 pixel
        triangle.mouvY(2);
        cross.mouvX(-2);
        diamond.mouvY(-2);

        square.drawShape(renderer); // Draw the shapes on the renderer
        triangle.drawShape(renderer);
        cross.drawShape(renderer);
        diamond.drawShape(renderer);

        renderer.show(30); // Show the screen at 30 FPS
        renderer.clearScreen({255, 0, 0}); // Clear the screen with a black background
    }
    return 0;
}