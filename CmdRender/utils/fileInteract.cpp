#include "fileInteract.h"

const std::vector<std::string> getFilenamesWithoutExtension(const std::string& path) {
    std::vector<std::string> filenames;

    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            // .stem() donne le nom sans l’extension
            filenames.push_back(entry.path().stem().string());
        }
    }

    return filenames;
}

std::string readFileToString(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + filePath);
    }

    std::ostringstream ss;
    ss << file.rdbuf();  // lit tout le contenu du fichier dans un stringstream
    return ss.str();
}