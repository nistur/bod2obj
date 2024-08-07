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
#include "vertex.h"

#include <vector>
#include <sstream>

Vertex::Vertex()
    : m_x(0)
    , m_y(0)
    , m_z(0)
    , m_isValid(false)
    , m_scale(1.f)
{
}

Vertex::Vertex(float scale)
    : m_x(0)
    , m_y(0)
    , m_z(0)
    , m_isValid(false)
    , m_scale(scale)
{
}

Vertex::Vertex(float x, float y, float z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
    , m_scale(1)
    , m_isValid(true)
{
}

bool Vertex::readBOD(std::string line)
{
    m_x = m_y = m_z = 0;
    m_isValid = false;
    auto coords = readBODInts(line, 3);
    // seems to take -1; -1; -1; as a sentinel for end of vert data
    if(((*coords).size() != 3) ||
       ( ( (*coords)[0] == -1 ) &&
	 ( (*coords)[1] == -1 ) &&
	 ( (*coords)[2] == -1 ) ))
	return false;
    m_x = (*coords)[0];
    m_y = (*coords)[1];
    m_z = (*coords)[2];
    m_isValid = true;
    return true;
}

bool Vertex::writeBOD(std::string& line)
{
    return false;
}

bool Vertex::readOBJ(std::string line)
{
    return false;
}
