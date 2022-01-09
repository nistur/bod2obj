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
#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <string>

#include "object.h"
//#include "bod.h"
//#include "obj.h"

/* Vertex
 * Represents a vertex in the model, just X,Y,Z plus a scale that is being applied to the 
 * whole model.
 */
class Vertex : public SharedObject<Vertex>//, public BOD<Vertex>, public OBJ<Vertex>
{
public:
    Vertex();
    Vertex(float scale);
    Vertex(float x, float y, float z);
    virtual ~Vertex(){};

    bool readBOD(std::string line);
    bool writeBOD(std::string& line);

    bool readOBJ(std::string line);
    bool writeOBJ(std::string& line);
    
private:
    float m_x, m_y, m_z;
    
    bool m_isValid;
    float m_scale;
};

#endif/*__VERTEX_H__*/
