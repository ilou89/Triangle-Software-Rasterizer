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
                tempIndex.push_back(index - 1);
            }

            indices.push_back(tempIndex);

        } else {
            std::cout << line << std::endl;
        }
    }
}

int
ModelLoader::verticesSize()
{
    return static_cast<int>(vertices.size());
}

int
ModelLoader::indicesSize()
{
    return static_cast<int>(indices.size());
}

std::vector<int>
ModelLoader::getIndicesAt(int index)
{
    return indices[index];
}

Vec3f
ModelLoader::getVerticesAt(int index)
{
    return vertices[index];
}

const std::vector<std::vector<int>>&
ModelLoader::getIndices()
{
    return indices;
}
