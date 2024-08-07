#include "obj.h"
#include <format>

OBJ::OBJ(){}

void OBJ::Read(Body::Ptr body, std::ifstream& file)
{
    // ERROR: NOT IMPLEMENTED
}

void OBJ::Write(Body::Ptr body, std::ofstream& file)
{
    // format is:
    // v x y z
    // values are floating point
    for(auto vert : body->vertices)
    {
	file << std::format("v {} {} {}", vert->X(), vert->Y(), vert->Z()) << std::endl;
    }

    
    // format is:
    // f v1 v2 v3
    // but indices are 1-indexed
    for(auto tri : body->triangles)
    {
	file << std::format("f {} {} {}", tri->v1+1, tri->v2+1, tri->v3+1) << std::endl;
    }
}
