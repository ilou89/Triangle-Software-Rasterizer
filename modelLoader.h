#ifndef __MODELLOADER_H__
#define __MODELLOADER_H__

#include "geometry.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
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

    int verticesSize();
    int indicesSize();
    std::vector<int> getIndicesAt(int index);
    Vec3f getVerticesAt(int index);
};

#endif //__MODELLOADER_H__

