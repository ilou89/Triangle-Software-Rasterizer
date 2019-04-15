#ifndef __MODLOADER_H__
#define __MODLOADER_H__

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "geometry.h"
#include <vector>

class ModelLoader {
private:
    std::vector<Vec3f> vertices;
    std::vector<std::vector<int>> indices;

    void fillVectors(std::ifstream& myfile);

public:
    ModelLoader();
    ~ModelLoader();
    bool loadFile(std::string filename);
};

#endif //__MODLOADER_H__
