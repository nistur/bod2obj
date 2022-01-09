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

#include "body.h"
#include "model.h"

class BOD : Model
{
public:
    BOD();
    virtual ~BOD(){}
    void Read(Body::Ptr body, std::ifstream& file);
    void Write(Body::Ptr body, std::ofstream& file);

private:
    typedef enum
    {
	BODY_SIZE,
	VERTICES,
	TRIANGLES,
	END,
    } Section;
    
    std::string NextToken(std::ifstream& file);
};

#endif/*__BOD_H__*/
