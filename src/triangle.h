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
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "object.h"
//#include "bod.h"
//#include "obj.h"

class Triangle : public SharedObject<Triangle>//, public BOD<Triangle>, public OBJ<Triangle>
{
public:
    Triangle();
    Triangle(int v1, int v2, int v3);
    virtual ~Triangle(){};

    bool readBOD(std::string line);
    bool writeBOD(std::string& line);

    bool readOBJ(std::string line);

//private:
    int v1,v2,v3;
};

#endif/*__TRIANGLE_H__*/
