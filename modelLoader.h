#ifndef __OBJLOADER_H__
#define __OBJLOADER_H__

#include <string>

class ObjLoader {
public:
    ObjLoader();
    ~ObjLoader();
    bool loadFile(std::string filename);
};

#endif //__OBJLOADER_H__
