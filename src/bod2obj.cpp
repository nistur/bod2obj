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

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <list>
#include <exception>

#include "vertex.h"
#include "triangle.h"
#include "body.h"

#include "bod.h"

typedef std::list<Body::Ptr> bodylist;
typedef bodylist::iterator bodyIter;

bodylist bodies;

bool skipEmpty(std::ifstream& stream, std::string& line);

int main(int argc, char** argv)
{
    std::string line;
    float scale = 1;

    if(argc == 1)
    {
	std::cerr << "Please provide input filename:" << std::endl;
	std::cerr << "    " << argv[0] << " filename.bod" << std::endl;
	return 1;
    }
    
    std::string infile = argv[1];
    std::string outfile;
    
    if(argc > 2)
    {
	outfile = argv[2];
    }
    else
    {
	outfile = infile.substr(0,infile.find_last_of("."));
    }
    std::cout << "Converting " << infile << " (" << outfile << ")" << std::endl;

    std::ifstream bodfile(infile);
    BOD bod;
    int i = 0;
//    while(!bodfile.eof())
    {
	printf("Reading LOD %d\n", i);
	Body::Ptr testbody = Body::Create();
	testbody->LOD = i;
	bod.Read(testbody, bodfile);
	bodies.push_back(testbody);
	++i;
    }

    
    for(bodyIter iBody = bodies.begin(); iBody != bodies.end(); ++iBody)
    {
	std::ostringstream filename;
	filename << outfile << "_LOD" << (*iBody)->LOD << ".obj";
	std::ofstream objfile(filename.str(), std::ios::trunc);

	printf("Writing %s (%lu/%lu)\n", filename.str().c_str(), (*iBody)->vertices.size(), (*iBody)->triangles.size());
	if(objfile.is_open())
	{
	    for(auto iVert = (*iBody)->vertices.begin(); iVert != (*iBody)->vertices.end(); ++iVert)
	    {
		std::string line;
		if((*iVert)->writeOBJ(line))
		{
		    objfile << line;
		}
	    }
	    for(auto iTri = (*iBody)->triangles.begin(); iTri != (*iBody)->triangles.end(); ++iTri)
	    {
		std::string line;
		if((*iTri)->writeOBJ(line))
		{
		    objfile << line;
		}
	    }
	    objfile.close();
	}
    }
    return 0;
}

bool skipEmpty(std::ifstream& stream, std::string& line)
{
    line = "";
    while(line.length() <= 1)
    {
	if(stream.eof()) return false;
	getline(stream, line);
	std::regex comment_regex("//.*");
	std::string newline = std::regex_replace( line, comment_regex, "");
	line = newline;
    }
    return true;
}
