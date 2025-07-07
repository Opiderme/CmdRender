#ifndef CMDRENDER_H_INCLUDED
#define CMDRENDER_H_INCLUDED
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
using namespace std;

class CmdRender {
public:
    string name;
    int width;
    int height;
    vector<vector<vector<int>>> screen;

    CmdRender(string n, int w, int h, vector<int> color);
    ~CmdRender();

    void show(int fps);
    void clearScreen(vector<int> color = {0, 0, 0}); // Default to black background

    void drawPoint(int x, int y, vector<int> color);
    void drawLine(int x1, int y1, int x2, int y2, vector<int> color);
    void drawPolygon(const vector<pair<int, int>>& points, vector<int> color, vector<int> colorFill);
    void drawCircle(int cx, int cy, int radius, vector<int> color, vector<int> colorFill);

private:
};

#endif //