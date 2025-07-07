#include "CmdRender.h"

CmdRender::CmdRender(string n, int w, int h, vector<int> color) : name(n), width(w), height(h), screen(h, vector<vector<int>>(w, color)) {  
}

CmdRender::~CmdRender() {
    // Destructor logic if needed
}

void CmdRender::show(int fps) {
    using namespace std::chrono;
    auto frameDuration = milliseconds(1000 / fps);
    auto start = high_resolution_clock::now();

    std::ostringstream oss;
    oss << "\033[H"; // Replace cursor at top-left

    // Génération de l'écran coloré en une seule passe
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const auto& rgb = screen[y][x];
            oss << "\033[38;2;"
                << rgb[0] << ";" << rgb[1] << ";" << rgb[2]
                << "mA"; // caractère affiché
        }
        oss << "\033[0m\n"; // Reset couleur + retour à la ligne
    }

    // Affichage en une fois (beaucoup plus rapide)
    std::cout << oss.str() << std::flush;

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