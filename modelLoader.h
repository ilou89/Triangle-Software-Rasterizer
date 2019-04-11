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
    void loadVertices(std::string& line);
    std::vector<Vec3f> vec3_v;
    std::vector<Vec3f> vec3_vt;
    std::vector<Vec3f> vec3_vn;

    std::vector<Vec3i> vertexIndices;
    std::vector<Vec3i> uvIndices;
    std::vector<Vec3i> normalIndices;

public:
    ModelLoader();
    ~ModelLoader();
    bool loadFile(std::string filename);
};

#endif //__MODLOADER_H__
