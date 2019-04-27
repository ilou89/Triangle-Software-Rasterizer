#ifndef __UTILS_H__
#define __UTILS_H__

struct Vertex {
    unsigned int x;
    unsigned int y;

    Vertex()
     : x(0), y(0) {}

    Vertex(unsigned int x, unsigned int y)
     : x(x), y(y) {}
};

#endif //__UTILS_H__
