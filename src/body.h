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

#ifndef __BODY_H__
#define __BODY_H__

#include "object.h"
#include "vertex.h"
#include "triangle.h"

#include <list>

class Body : public SharedObject<Body>
{
public:
    typedef std::list<Vertex::Ptr> vertexlist;
    typedef vertexlist::iterator vertIter;
    typedef std::list<Triangle::Ptr> trilist;
    typedef trilist::iterator triIter;

    vertexlist vertices;
    trilist triangles;
    int LOD;
};

#endif/*__BODY_H__*/
