#ifndef VERTEX_H
#define VERTEX_H

#include "Math.hpp"
#include <vector>

namespace paint {

struct Vertex {
    std::vector<Vec2> vertexArray;
    std::vector<Index> indexArray; //3 indices (2 are vertex indices, and final index is the normal index)
    std::vector<Vec2> normalArray; //normal vector corresponding to the above index specified lines
};

}

#endif VERTEX_H