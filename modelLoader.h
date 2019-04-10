#ifndef __MODLOADER_H__
#define __MODLOADER_H__

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "geometry.h"

class ModelLoader {
private:
    void loadVertices(std::string& line);

public:
    ModelLoader();
    ~ModelLoader();
    bool loadFile(std::string filename);
};

#endif //__MODLOADER_H__
