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
	if (filename.compare(filename.length() - 4, 4, ".obj")) {
		return false;
	}

    std::ifstream myfile(filename);

    if (!myfile.is_open()) {
        return false;
    }

   fillVectors(myfile);

    myfile.close();

    return true;
}

void
ModelLoader::fillVectors(std::ifstream& myfile)
{
    std::string line;

    while (getline(myfile, line)) {
        std::istringstream stream(line);

        if (!line.compare(0, 2, "v ")) {
            Vec3f v;
            char trash;
            stream >> trash;
            stream >> v.x;
            stream >> v.y;
            stream >> v.z;
            vec3_v.push_back(v);

        } else if (!line.compare(0, 2, "f ")) {
			std::vector<int> indices;
            char trash;
            stream >> trash;
			int index;

            for (int i = 0; i < 3; ++i) {
                stream >> index;
				indices.push_back(index);
                stream >> trash;
                stream >> index;
                stream >> trash;
                stream >> index;
            }

        } else {
            std::cout << line << std::endl;
        }
    }

}
