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
	void fillVectors(std::ifstream& myfile);
    std::vector<Vec3f> vec3_v;
    std::vector<std::vector<int>> vertexIndices;

public:
    ModelLoader();
    ~ModelLoader();
    bool loadFile(std::string filename);
};

#endif //__MODLOADER_H__
