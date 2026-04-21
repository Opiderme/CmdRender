#include "fileInteract.h"
#include <dirent.h>

const std::vector<std::string> getFilenamesWithoutExtension(const std::string& path) {
    std::vector<std::string> filenames;

    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string filename = ent->d_name;
            if (filename != "." && filename != "..") {
                size_t lastdot = filename.find_last_of(".");
                if (lastdot == std::string::npos) {
                    filenames.push_back(filename);
                } else {
                    filenames.push_back(filename.substr(0, lastdot));
                }
            }
        }
        closedir(dir);
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