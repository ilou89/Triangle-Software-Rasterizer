#include "modelLoader.h"

ModelLoader::ModelLoader()
{

}

ModelLoader::~ModelLoader()
{

}

bool
ModelLoader::loadFile(std::string filename)
{
    std::string line;
    std::ifstream myfile(filename);

    if(!myfile.is_open()) {
        return false;
    }

    while(getline(myfile, line)) {
        std::istringstream stream(line);
        if(!line.compare(0, 2, "v ")) {
            std::cout << line << std::endl;
            char trash;
            stream >> trash;
            float x, y, z;
            stream >> x;
            stream >> y;
            stream >> z;
            Vec3f vec3(x, y, z);
        }
    }

    myfile.close();

    return true;
}

void
ModelLoader::loadVertices(std::string& line)
{

}
