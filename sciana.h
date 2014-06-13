#ifndef SCIANA_H
#define SCIANA_H
#include "pole.h"
class Sciana : public Pole
{
public:
    Sciana();

    bool Gwall;
    bool Pwall;
    bool Dwall;
    bool Lwall;
};

#endif // SCIANA_H
