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
#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <memory>
#include <string>
#include <sstream>
#include <vector>

extern const std::string k_BODdelim;

template<typename base>
class SharedObject
{
public:
    typedef std::shared_ptr<base> Ptr;
    
    static Ptr Create()
    {
	return std::make_shared<base>();
    }

    template<typename param>
    static Ptr Create(param p)
    {
	return std::make_shared<base>(p);
    }

    template<typename ... Args>
    static Ptr Create( Args ... args )
    {
	return std::make_shared<base>(args ...);
    }
    
    protected:
    enum Type
    {
	Vertex,
	Triangle,
    };

    template<typename type>
    bool writeOBJArray(Type t, std::string& line, std::vector<type> dat)
    {
	if( dat.size() <= 0 )
	{
	    return false;
	}
	std::ostringstream tridata;
	tridata << (t == Vertex ? "v " : "f ") ;
	for(int i = 0; i < dat.size() - 1; ++i)
	{
	    tridata << dat[i] << " ";
	}
	tridata << dat[dat.size() - 1] << std::endl;
	line = tridata.str();
	return true;
    }
    
protected:
    typedef struct
    {
    public:
	int intVal;
	float floatVal;
	std::string strVal;
    } MixedType;
    
    typedef std::vector<int> intVec;
    typedef std::shared_ptr<intVec> intVecPtr;
    typedef std::vector<MixedType> mixVec;
    typedef std::shared_ptr<mixVec> mixVecPtr;

public:
    typedef std::shared_ptr<base> sPtr;
    template<typename param>
    static sPtr CreateFromBOD(std::string& line, param p)
    {
	auto object = base::Create(p);
	if(object->readBOD(line))
	{
	    return object;
	}
	return nullptr;
    }
    static sPtr CreateFromBOD(std::string& line)
    {
	auto object = base::Create();
	if(object->readBOD(line))
	{
	    return object;
	}
	return nullptr;
    }
protected:
    intVecPtr readBODInts(std::string line, size_t capacity = 0)
    {
	intVecPtr ints = std::make_shared<intVec>();
	if(capacity > 0)
	{
	    ints->reserve(capacity);
	}
	size_t pos = 0;
	while((pos = line.find(k_BODdelim)) != std::string::npos)
	{
	    ints->push_back(atoi(line.substr(0,pos).c_str()));
	    line.erase(0, pos + k_BODdelim.length());
	}

	return ints;
    }
    
    mixVecPtr readBODMixed(std::string line, size_t capacity = 0)
    {
	mixVecPtr dat = std::make_shared<mixVec>();
	if(capacity > 0)
	{
	    dat->reserve(capacity);
	}
	
	size_t pos = 0;
	while((pos = line.find(k_BODdelim)) != std::string::npos)
	{
	    MixedType type;
	    type.strVal = line.substr(0,pos);
	    type.intVal = atoi(type.strVal.c_str());
	    type.floatVal = atof(type.strVal.c_str());
	    dat->push_back(type);
	    
	    line.erase(0, pos + k_BODdelim.length());
	}
	return dat;
    }
};

#endif/*__OBJECT_H__*/
