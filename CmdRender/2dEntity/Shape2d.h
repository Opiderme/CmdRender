#ifndef SHAPE2D_H_INCLUDED
#define SHAPE2D_H_INCLUDED
#include <string>
#include <vector>
#include <iostream>
#include "../CmdRender.h"
using namespace std;

class Shape2d {
public:
    Shape2d(string f, int px, int py, int w, int h, vector<int> color, vector<int> colorFill);
    Shape2d(string f, int px, int py, int w, int h, vector<int> color, vector<int> colorFill, vector<pair<int, int>>& pts);
    ~Shape2d();

    void drawShape(CmdRender& screen) const;

    void setOrigin(int x, int y);

    void setPosition(int x, int y);

    void mouvX(int dx);
    void mouvY(int dy);


private:
    string forme;
    int positionX;
    int positionY;
    int width;
    int height;
    pair<int, int> origin;
    std::vector<std::pair<int, int>> points;
    vector<int> color;
    vector<int> colorFill;
};

#endif //