/*
  Copyright (c) 2021 Philipp Geyer [Nistur]

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
  claim that you wrote the original software. If you use this software
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "triangle.h"

#include <sstream>
#include <regex>

Triangle::Triangle()
{
}

Triangle::Triangle(int v1, int v2, int v3)
    : v1(v1)
    , v2(v2)
    , v3(v3)
{}

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
