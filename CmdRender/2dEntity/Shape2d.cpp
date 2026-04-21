#include "Shape2d.h"
#include "../utils/fileInteract.h"

const string FOLDER_2D_ENTITY = "CmdRender/prefab2d/";

pair<int, int> parseCoord(const string& s) {
    int x, y;
    char comma;
    istringstream ss(s);
    ss >> x >> comma >> y;
    return {x, y};
}

Shape2d::Shape2d(string f, int px, int py, int w, int h, vector<int> color, vector<int> colorFill) : forme(f), positionX(px), positionY(py), width(w), height(h), color(color), colorFill(colorFill) {
    if (f.empty()) {
        std::cerr << "File name cannot be empty." << std::endl;
        return;
    }
    // if f finish with .cmdr, remove it
    if (f.size() >= 5 && f.substr(f.size() - 5) == ".cmdr") {
        f = f.substr(0, f.size() - 5);
    }
    std::vector<std::string> filenamesWithoutExtension = getFilenamesWithoutExtension(FOLDER_2D_ENTITY);
    if (filenamesWithoutExtension.empty()) {
        std::cerr << "No files found in the directory: " << FOLDER_2D_ENTITY << std::endl;
        return;
    }
    for (size_t i = 0; i < filenamesWithoutExtension.size(); ++i) {
        if (filenamesWithoutExtension[i] == f) {
            std::cout << "File found: " << filenamesWithoutExtension[i] << std::endl;
            break;
        }
        if (i == filenamesWithoutExtension.size() - 1) {
            std::cerr << "File not found: " << f << "Acquired default shape: square" << std::endl;
            this->forme = "square";
        }
    }
    string shapeData = readFileToString(FOLDER_2D_ENTITY + this->forme + ".cmdr");
    std::istringstream iss(shapeData);
    std::vector<std::string> tokens;
    std::string word;
    while (iss >> word) {
        tokens.push_back(word);
    }

    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i] == "O") {
            if (i + 1 < tokens.size()) {
                pair<int, int> o = parseCoord(tokens[i + 1]);
                this->origin = {o.first + this->positionX, o.second + this->positionY};
            }
        } else if (tokens[i] == "P") {
            for (size_t j = i + 1; j < tokens.size(); ++j) {
                pair<int, int> p = parseCoord(tokens[j]);
                this->points.push_back({p.first * this->width + this->positionX, p.second * this->height + this->positionY});
            }
            break; // Tout ce qui vient après "P" a été traité
        }
    }

    // Affichage pour vérification
    cout << "Origin: {" << this->origin.first << ", " << this->origin.second << "}" << endl;
    cout << "Points: ";
    for (const auto& p : this->points) {
        cout << "{" << p.first << ", " << p.second << "} ";
    }
    cout << endl;
    //std::cout << "Shape data read from file: " << FOLDER_2D_ENTITY + this->forme + ".cmdr : " << shapeData << std::endl;
}
Shape2d::Shape2d(string f, int px, int py, int w, int h, vector<int> color, vector<int> colorFill, vector<pair<int, int>>& pts) : forme(f), positionX(px), positionY(py), width(w), height(h), points(pts), color(color), colorFill(colorFill) {
    if (f.empty()) {
        std::cerr << "File name cannot be empty." << std::endl;
        return;
    }
    // if f finish with .cmdr, remove it
    if (f.size() >= 5 && f.substr(f.size() - 5) == ".cmdr") {
        f = f.substr(0, f.size() - 5);
    }
    std::vector<std::string> filenamesWithoutExtension = getFilenamesWithoutExtension(FOLDER_2D_ENTITY);
    if (filenamesWithoutExtension.empty()) {
        std::cerr << "No files found in the directory: " << FOLDER_2D_ENTITY << std::endl;
        return;
    }
    for (size_t i = 0; i < filenamesWithoutExtension.size(); ++i) {
        if (filenamesWithoutExtension[i] == f) {
            std::cout << "File found: " << filenamesWithoutExtension[i] << std::endl;
            break;
        }
        if (i == filenamesWithoutExtension.size() - 1) {
            std::cerr << "File not found: " << f << "Acquired default shape: square" << std::endl;
            this->forme = "square";
        }
    }
    
}

Shape2d::~Shape2d() {
    // Destructor logic if needed
}

void Shape2d::drawShape(CmdRender& screen) const {
    if (this->points.empty()) {
        std::cerr << "No points to draw for shape: " << this->forme << std::endl;
        return;
    }
    // Draw the shape using the points and colors
    screen.drawPolygon(this->points, this->color, this->colorFill);
}

void Shape2d::setOrigin(int x, int y) {
    this->origin = {x, y};
}

void Shape2d::setPosition(int x, int y) {
    this->positionX = x;
    this->positionY = y;
    int tempX = this->points[0].first;
    int tempY = this->points[0].second;
    // Update points based on new position
    for (auto& p : this->points) {
        p.first += x - tempX;
        p.second += y - tempY;
    }
}

void Shape2d::mouvX(int dx) {
    this->positionX += dx;
    for (auto& p : this->points) {
        p.first += dx;
    }
}

void Shape2d::mouvY(int dy) {
    this->positionY += dy;
    for (auto& p : this->points) {
        p.second += dy;
    }
}