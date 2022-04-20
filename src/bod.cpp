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
#include "bod.h"
#include <string>
#include <iostream>
#include <regex>
#include <csignal>

BOD::BOD(){}

void BOD::Read(Body::Ptr body, std::ifstream& file)
{
    std::string line;
    // skip the first metadata
    // not currently got  good way of doing this, apart from just scanning forward
    // for it
    while(line.rfind("// beginning of body 1") == std::string::npos)
    {
	std::getline(file, line);
    }

    Section currentSection = BODY_SIZE;
    
    int i = 0;

    float scale = 1;
    scale /= 2000.f;
    while(currentSection != END)
    {
	switch(currentSection)
	{
	case BODY_SIZE:
	{
	    float bodysize = atof(NextToken(file).c_str());
	    bodysize /= 5000.f;
	    scale *= bodysize;
	    currentSection = VERTICES;
	    break;
	}
	case VERTICES:
	{
	    float x = atoi(NextToken(file).c_str());
	    float y = atoi(NextToken(file).c_str());
	    float z = atoi(NextToken(file).c_str());
	    
	    if(x == -1 && y == -1 && z == -1 )
	    {
		currentSection = TRIANGLES;
	    }
	    else
	    {
		body->vertices.push_back(Vertex::Create(x*scale, y*scale, z*scale));
	    }
	    break;
	}
	case TRIANGLES:
	{
	    int flag = atoi(NextToken(file).c_str());
	    if( flag == -99 )
	    {
		auto token = NextToken(file);
	        int section = atoi(token.c_str());
//		if(section == 0 )
		{
		    currentSection = END;
		}
	    }

	    else
	    {
		int vert1 = atoi(NextToken(file).c_str());
		int vert2 = atoi(NextToken(file).c_str());
		int vert3 = atoi(NextToken(file).c_str());

		int n1 = atoi(NextToken(file).c_str());
		auto n2 = NextToken(file);


		float u1;

		if(std::count(n2.begin(), n2.end(), '.') > 0 )
		{
		    u1 = atof(n2.c_str());
		}
		else
		{
		    u1 = atof(NextToken(file).c_str());
		}
		float v1 = atof(NextToken(file).c_str());
		float u2 = atof(NextToken(file).c_str());
		float v2 = atof(NextToken(file).c_str());
		float u3 = atof(NextToken(file).c_str());
		float v3 = atof(NextToken(file).c_str());

		body->triangles.push_back(Triangle::Create(vert1, vert2, vert3));
		++i;
	    }
	    
	    break;
	}
	default:
	{}
	}
    }
}

void BOD::Write(Body::Ptr body, std::ofstream& file)
{
    // ERROR: NOT IMPLEMENTED
}

std::string BOD::NextToken(std::ifstream& file)
{
    std::string line;

    bool in_block = false;
    while(line.size() == 0 && !file.eof())
    {
	std::getline(file, line, ';');
	std::regex comment_regex("//.*");
	line = std::regex_replace( line, comment_regex, "");
	std::regex whitespace_regex("^\\s+|\\s+$");
	line = std::regex_replace(line, whitespace_regex, "");


	// Currently don't handle /! ... !/ blocks, so just skip everything that's in them
	// this is because I am splitting the line on ; which gives me (for example)
	// /! N: { 0.12345
	// in the first token, and then
	//  } !/
	// in the last token of the block
	// The ideal thing is to put in a read-ahead and block the whole thing together into
	// one token, but then my problem is that I am not currently sure if every triangle
	// will have a normal block, and every body has a collision box at the end, so I'd
	// have to put in expectations, and rewinding if it's not the case or something
	// On the todo list, but not now.

	std::regex block_stop("^.*!/");
	std::string newline = std::regex_replace(line, block_stop, "");
	if(newline.size() != line.size())
	{
	    in_block = false;
	    line = newline;
	}

	std::regex block_start("/!.*$");
	newline = std::regex_replace(line, block_start, "");
	if(newline.size() != line.size())
	{
	    line = newline;
	    in_block = true;
	}
	
	if(in_block)
	{
	    line = "";
	}
    }
    
    return line;
}
