#include "CmdRender.h"

CmdRender::CmdRender(string n, int w, int h, vector<int> color) : name(n), width(w), height(h), screen(h, vector<vector<int>>(w, color)), previousScreen(h, vector<vector<int>>(w, {-1, -1, -1})) {
}

CmdRender::~CmdRender() {
    // Destructor logic if needed
}

void CmdRender::show(int fps) {
    using namespace std::chrono;
    auto frameDuration = milliseconds(1000 / fps);
    auto start = high_resolution_clock::now();

    std::ostringstream oss;

    // Dynamic Terminal Output: only render changed pixels
    int lastR = -1, lastG = -1, lastB = -1;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const auto& rgb = screen[y][x];
            const auto& prevRgb = previousScreen[y][x];

            // Only output if the pixel color has changed
            if (rgb != prevRgb) {
                // Move cursor to specific position (ANSI coordinates are 1-based)
                oss << "\033[" << (y + 1) << ";" << (x + 1) << "H";

                if (rgb[0] != lastR || rgb[1] != lastG || rgb[2] != lastB) {
                    oss << "\033[38;2;"
                        << rgb[0] << ";" << rgb[1] << ";" << rgb[2]
                        << "m";
                    lastR = rgb[0];
                    lastG = rgb[1];
                    lastB = rgb[2];
                }
                oss << "A"; // caractère affiché

                // Update previous screen
                previousScreen[y][x] = rgb;
            }
        }
    }
    // We only output if there were any changes
    if (!oss.str().empty()) {
        oss << "\033[0m"; // Reset couleur at the very end
        std::cout << oss.str() << std::flush;
    }

    // Synchronisation à la bonne durée d'une frame
    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<milliseconds>(end - start);

    if (elapsed < frameDuration) {
        std::this_thread::sleep_for(frameDuration - elapsed);
    }
}


void CmdRender::clearScreen(vector<int> color) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            screen[y][x] = color;
        }
    }
}

void CmdRender::drawPoint(int x, int y, vector<int> color) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        screen[y][x] = color;
    }
}

void CmdRender::drawLine(int x1, int y1, int x2, int y2, vector<int> color) {
    // Simple Bresenham's line algorithm
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        drawPoint(x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void CmdRender::drawPolygon(const vector<pair<int, int>>& points, vector<int> color, vector<int> colorFill) {
    if (points.size() < 3) return; // Need at least 3 points to form a polygon

    // Dessiner les bords
    for (size_t i = 0; i < points.size(); ++i) {
        int x1 = points[i].first;
        int y1 = points[i].second;
        int x2 = points[(i + 1) % points.size()].first;
        int y2 = points[(i + 1) % points.size()].second;
        drawLine(x1, y1, x2, y2, color);
    }

    // Remplissage simple (scanline fill)
    for (int y = 0; y < height; ++y) {
        bool inside = false;
        for (int x = 0; x < width; ++x) {
            // Check if the point is inside the polygon using ray-casting algorithm
            bool isInside = false;
            for (size_t i = 0, j = points.size() - 1; i < points.size(); j = i++) {
                if ((points[i].second > y) != (points[j].second > y) &&
                    (x < (points[j].first - points[i].first) * (y - points[i].second) / (points[j].second - points[i].second) + points[i].first)) {
                    isInside = !isInside;
                }
            }
            if (isInside) {
                if (!inside) {
                    inside = true;
                }
                screen[y][x] = colorFill; // Fill the pixel
            } else {
                inside = false;
            }
        }
    }
}

void CmdRender::drawCircle(int cx, int cy, int radius, vector<int> color, vector<int> colorFill) {
    if (radius <= 0) return;

    // Draw the circle outline using Midpoint Circle Algorithm
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        drawPoint(cx + x, cy + y, color);
        drawPoint(cx + y, cy + x, color);
        drawPoint(cx - y, cy + x, color);
        drawPoint(cx - x, cy + y, color);
        drawPoint(cx - x, cy - y, color);
        drawPoint(cx - y, cy - x, color);
        drawPoint(cx + y, cy - x, color);
        drawPoint(cx + x, cy - y, color);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }

    // Fill the circle
    for (int i = -radius; i <= radius; ++i) {
        for (int j = -radius; j <= radius; ++j) {
            if (i * i + j * j <= radius * radius) {
                drawPoint(cx + i, cy + j, colorFill);
            }
        }
    }
}