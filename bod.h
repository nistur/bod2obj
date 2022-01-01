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
#ifndef __BOD_H__
#define __BOD_H__

#include <vector>

template<typename base>
class BODObject
{
public:
    typedef std::shared_ptr<base> Ptr;

    template<typename param>
    static Ptr Create(std::string& line, param p)
    {
	Ptr object = std::make_shared<base>(p);
	if(object->readBOD(line))
	{
	    return object;
	}
	return nullptr;
    }
    
    static Ptr Create(std::string& line)
    {
	Ptr object = std::make_shared<base>();
	if(object->readBOD(line))
	{
	    return object;
	}
	return nullptr;
    }

protected:
    typedef std::vector<int> intVec;
    typedef std::shared_ptr<intVec> intVecPtr;

    intVecPtr readBODInts(std::string line, size_t capacity = 0)
    {
	intVecPtr ints = std::make_shared<intVec>();
	if(capacity > 0)
	{
	    ints->reserve(capacity);
	}
	static const std::string delim = ";";
	size_t pos = 0;
	while((pos = line.find(delim)) != std::string::npos)
	{
	    ints->push_back(atoi(line.substr(0,pos).c_str()));
	    line.erase(0, pos + delim.length());
	}

	return ints;
    }
};

#endif/*__BOD_H__*/
