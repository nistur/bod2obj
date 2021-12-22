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
#include <regex>
#include <list>
#include <exception>

class vertex
{
public:
    int x, y, z;
};

class triangle
{
public:
    int v1, v2, v3;
};

typedef std::list<vertex> vertexlist;
typedef vertexlist::iterator vertIter;
typedef std::list<triangle> trilist;
typedef trilist::iterator triIter;

class body
{
public:
    vertexlist vertices;
    trilist triangles;
    int LOD;
};

typedef std::list<body> bodylist;
typedef bodylist::iterator bodyIter;

bodylist bodies;

bool skipEmpty(std::ifstream& stream, std::string& line);
bool createVertex(std::string line, vertex& vert);
bool createTriangle(std::string line, triangle& tri, int indexStart);

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


    try
    {
	std::ifstream bodfile (infile);
	
	if(bodfile.is_open())
	{
	    while(std::count_if(line.begin(), line.end(), [](char c) { return c == ';'; }) != 1)
	    {
		skipEmpty(bodfile, line);
	    }
	    
	    float bodysize = (float)atoi(line.c_str());
	    bodysize /= 5000;

	    skipEmpty(bodfile, line);
	    
	    scale /= 2000.f;
	    scale *= bodysize;
	    
	    int i = 0;
	    while(!bodfile.eof())
	    {
		body body;
		body.LOD = i;
		vertex v;
		while(createVertex(line, v))
		{
		    body.vertices.push_back(v);
		    skipEmpty(bodfile, line);
		}
		if( body.vertices.empty() )
		{
		    std::cerr << "Could not find vertices" << std::endl;
		    return 1;
		}
		body.vertices.pop_back();
		
		
		triangle t;
		while(true)
		{
		    while(createTriangle(line, t, 0))
		    {
			body.triangles.push_back(t);
			skipEmpty(bodfile, line);
		    }
		    body.triangles.pop_back();
		    if(skipEmpty(bodfile, line) && // end part
		       skipEmpty(bodfile, line) ) // end body
		    {
			if(!createTriangle(line, t, 0))
			{
			    break;
			}
		    }
		}
		if(!skipEmpty(bodfile, line) || // body size
			!skipEmpty(bodfile, line)) // next vertex
		{
		    // eof
		}
		
		std::cout << "Vertices: (" << i << ") " << body.vertices.size() << std::endl;
		std::cout << "Triangles: (" << i << ") " << body.triangles.size() << std::endl;
		
		bodies.push_back(body);
		++i;
	    }
	    
	    bodfile.close();
	}
    }
    catch( std::exception e)
    {
	std::cerr << e.what() << std::endl;
	return 0;
    }
    
    for(bodyIter iBody = bodies.begin(); iBody != bodies.end(); ++iBody)
    {
	std::ostringstream filename;
	filename << outfile << "_LOD" << iBody->LOD << ".obj";
	std::ofstream objfile(filename.str(), std::ios::trunc);
	if(objfile.is_open())
	{
	    for(vertIter iVert = iBody->vertices.begin(); iVert != iBody->vertices.end(); ++iVert)
	    {
		objfile << "v ";
		objfile << ((float)iVert->x)*scale << " ";
		objfile << ((float)iVert->y)*scale << " ";
		objfile << ((float)iVert->z)*scale << std::endl;
	    }
	    for(triIter iTri = iBody->triangles.begin(); iTri != iBody->triangles.end(); ++iTri)
	    {
		objfile << "f ";
		objfile << 1+iTri->v1 << " ";
		objfile << 1+iTri->v2 << " ";
		objfile << 1+iTri->v3 << std::endl;
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

bool createVertex(std::string line, vertex& vert)
{
    std::string delim = ";";
    std::string token;
    size_t pos = 0;
    std::vector<int> coords;
    while((pos = line.find(delim)) != std::string::npos)
    {
	token = line.substr(0,pos);
	line.erase(0, pos + delim.length());
	coords.push_back(atoi(token.c_str()));
    }
    if((coords.size() != 3) ||
       ( coords[0] == coords[1] == coords[2] == -1))
	return false;
    vert.x = coords[0];
    vert.y = coords[1];
    vert.z = coords[2];
    return true;
}



bool createTriangle(std::string line, triangle& tri, int indexStart)
{
    std::regex comment_regex("/!.*!/");
    line = std::regex_replace( line, comment_regex, "");

    std::string delim = ";";
    std::string token;
    size_t pos = 0;
    std::vector<int> indices;
    int id = 0;
    while((pos = line.find(delim)) != std::string::npos)
    {
	token = line.substr(0,pos);
	line.erase(0, pos + delim.length());
	int val = atoi(token.c_str());
	if( id == 0 )
	{
	    if( val == -99)
	    {
		break;
	    }
	}
	else if( id < 4 )
	{
	    indices.push_back(indexStart + val);
	}
	else
	{
	    // don't care about other info?
	    break;
	}
	++id;
    }
    
    if( indices.size() != 3 )
    {
	return false;
    }
    tri.v1 = indices[0];
    tri.v2 = indices[1];
    tri.v3 = indices[2];
    return true;
}
