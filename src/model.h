#ifndef __MODEL_H__
#define __MODEL_H__

#include "body.h"
#include <fstream>

class Model
{
public:
    virtual void Read(Body::Ptr body, std::ifstream& file) = 0;
    virtual void Write(Body::Ptr body, std::ofstream& file) = 0;
};

#endif/*__MODEL_H__*/
