#include "triangle.h"

#include <sstream>
#include <regex>

Triangle::Triangle()
{
}

bool Triangle::readBOD(std::string line)
{
    std::regex comment_regex("/!.*!/");
    line = std::regex_replace( line, comment_regex, "");


    auto dat = readBODMixed(line, 32);

    if(dat->size() < 4)
    {
	return false;
    }
    
    v1 = (*dat)[1].intVal;
    v2 = (*dat)[2].intVal;
    v3 = (*dat)[3].intVal;
    return true;
}

bool Triangle::writeBOD(std::string& line)
{
    return false;
}

bool Triangle::readOBJ(std::string line)
{
    return false;
}

bool Triangle::writeOBJ(std::string& line)
{

    // format is:
    // f v1 v2 v3
    // but indices are 1-indexed
    
    std::ostringstream tridata;
    tridata << "f ";
    tridata << 1+v1 << " ";
    tridata << 1+v2 << " ";
    tridata << 1+v3 << std::endl;
    line = tridata.str();
    return true;
}
