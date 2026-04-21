#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "CmdRender/CmdRender.h"
#include "CmdRender/2dEntity/Shape2d.h"

using namespace std;

void testPoint() {
    cout << "Testing Point Rendering..." << endl;
    CmdRender renderer("TestPoint", 40, 20, {0, 0, 0});
    renderer.drawPoint(20, 10, {255, 0, 0}); // Red point in center
    renderer.show(1);
    this_thread::sleep_for(chrono::seconds(2));
    cout << "\033[0m\nPoint test completed." << endl;
}

void testLine() {
    cout << "Testing Line Rendering..." << endl;
    CmdRender renderer("TestLine", 40, 20, {0, 0, 0});
    renderer.drawLine(5, 5, 35, 15, {0, 255, 0}); // Green line
    renderer.show(1);
    this_thread::sleep_for(chrono::seconds(2));
    cout << "\033[0m\nLine test completed." << endl;
}

void testPolygon() {
    cout << "Testing Polygon Rendering..." << endl;
    CmdRender renderer("TestPolygon", 40, 20, {0, 0, 0});
    vector<pair<int, int>> points = {{10, 5}, {30, 5}, {20, 15}};
    renderer.drawPolygon(points, {0, 0, 255}, {255, 255, 0}); // Blue outline, Yellow fill
    renderer.show(1);
    this_thread::sleep_for(chrono::seconds(2));
    cout << "\033[0m\nPolygon test completed." << endl;
}

void testCircle() {
    cout << "Testing Circle Rendering..." << endl;
    CmdRender renderer("TestCircle", 40, 20, {0, 0, 0});
    renderer.drawCircle(20, 10, 8, {255, 0, 255}, {0, 255, 255}); // Magenta outline, Cyan fill
    renderer.show(1);
    this_thread::sleep_for(chrono::seconds(2));
    cout << "\033[0m\nCircle test completed." << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [point|line|polygon|circle|all]" << endl;
        return 1;
    }

    string testName = argv[1];

    if (testName == "point") {
        testPoint();
    } else if (testName == "line") {
        testLine();
    } else if (testName == "polygon") {
        testPolygon();
    } else if (testName == "circle") {
        testCircle();
    } else if (testName == "all") {
        testPoint();
        testLine();
        testPolygon();
        testCircle();
    } else {
        cerr << "Unknown test: " << testName << endl;
        return 1;
    }

    return 0;
}
