#include "modelLoader.h"
#include <cstdint>

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
            char trash;
            stream >> trash;
            float x, y, z;
            stream >> x;
            stream >> y;
            stream >> z;
            Vec3f v(x, y, z);
            vec3_v.push_back(v);
        } else if(!line.compare(0, 2, "vt")) {
            char trash;
            stream >> trash;
            float x, y, z;
            stream >> x;
            stream >> y;
            stream >> z;
            Vec3f vt(x, y, z);
            vec3_vt.push_back(vt);
        } else if(!line.compare(0, 2, "vn")) {
            char trash;
            stream >> trash;
            float x, y, z;
            stream >> x;
            stream >> y;
            stream >> z;
            Vec3f vn(x, y, z);
            vec3_vn.push_back(vn);
        } else if(!line.compare(0, 2, "f ")) {
            int vertexIndex[3];
            int uvIndex[3];
            int normalIndex[3];
            char trash;
            stream >> trash;

            for(int i = 0; i < 3; ++i) {
                stream >> vertexIndex[i];
                stream >> trash;

                stream >> uvIndex[i];
                stream >> trash;

                stream >> normalIndex[i];
            }
            Vec3i vertexIndexs(vertexIndex[0], vertexIndex[1], vertexIndex[2]);
            vertexIndices.push_back(vertexIndexs);
            Vec3i uvIndexs(uvIndex[0], uvIndex[1], uvIndex[2]);
            uvIndices.push_back(uvIndexs);
            Vec3i normalIndexs(normalIndex[0], normalIndex[1], normalIndex[2]);
            normalIndices.push_back(normalIndexs);
        } else {
            std::cout << line << std::endl;
        }
    }

    myfile.close();

    return true;
}

