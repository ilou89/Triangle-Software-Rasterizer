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

    while (std::getline(myfile, line)) {
        std::istringstream stream(line);

        if (!line.compare(0, 2, "v ")) {
            char space;
            Vec3f tempVertex;

            stream >> space;
            stream >> tempVertex.x;
            stream >> tempVertex.y;
            stream >> tempVertex.z;
            vertices.push_back(tempVertex);

        } else if (!line.compare(0, 2, "f ")) {
            std::vector<int> tempIndex;
            int index;
            char space;
            int dummy;

            stream >> space;

            for (int i = 0; i < 3; ++i) {
                stream >> index;
                stream >> space;

                stream >> dummy;
                stream >> space;

                stream >> dummy;
                tempIndex.push_back(index);
            }

            indices.push_back(tempIndex);

        } else {
            std::cout << line << std::endl;
        }
    }
}

